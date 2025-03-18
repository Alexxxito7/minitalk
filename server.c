/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alschnei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:44:48 by alschnei          #+#    #+#             */
/*   Updated: 2025/03/05 12:44:49 by alschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reset_message(char **message, int *len)
{
	write(1, *message, *len);
	write(1, "\n", 1);
	free(*message);
	*message = NULL;
	*len = 0;
}

void	append_char(char **message, int *len, char c)
{
	char	*temp;
	int		i;

	temp = malloc(*len + 2);
	if (!temp)
		return ;
	i = 0;
	while (i < *len)
	{
		temp[i] = (*message)[i];
		i++;
	}
	temp[*len] = c;
	temp[*len + 1] = '\0';
	free(*message);
	*message = temp;
	(*len)++;
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit;
	static int				len;
	static unsigned char	c;
	static char				*message;

	(void) context;
	(void) info;
	if (sig == SIGUSR1)
		c |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if (c == '\0')
		{
			reset_message(&message, &len);
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			append_char(&message, &len, c);
			kill(info->si_pid, SIGUSR1);
		}
		c = 0;
	}
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server running with PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
