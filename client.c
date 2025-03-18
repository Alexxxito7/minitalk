/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   client.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: alschnei <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/05 12:44:57 by alschnei		  #+#	#+#			 */
/*   Updated: 2025/03/05 12:44:59 by alschnei		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minitalk.h"

int	g_signalcheck = 1;

void	send_char(pid_t server_pid, char c)
{
	
	int	i;

	i = 8;
	while (i--)
	{
		g_signalcheck = 0;
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		if (g_signalcheck == 0)
			pause();
	}
}

void	send_message(int sig, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (sig == SIGUSR2)
	{
		ft_printf("Server received message\n");
		exit(1);
	}
	g_signalcheck = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int	i;

	i = 0;
	sa.sa_sigaction = send_message;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid_t	server_pid;

	if (argc != 3)
		return (write(1, "Usage: ./client <server_pid> <message>\n", 39), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (write(1, "Invalid PID\n", 12), 1);
	if (kill(server_pid, 0) != 0)
		return (write(1, "Invalid PID or Server unreachable\n", 35), 1);
	while (argv[2][i])
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
