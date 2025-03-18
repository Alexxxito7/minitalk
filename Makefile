# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alschnei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 13:14:14 by alschnei          #+#    #+#              #
#    Updated: 2025/03/03 13:14:16 by alschnei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Paths
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_INC = -I$(FT_PRINTF_DIR)

LIBFT_DIR = ./ft_libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

# Source files
SRCS_CLIENT = client.c
SRCS_SERVER = server.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

# Executable names
NAME_CLIENT = client
NAME_SERVER = server

# Compilation settings
CC = cc
CFLAGS = -Wall -Wextra -Werror $(FT_PRINTF_INC) $(LIBFT_INC)

# Default target
all: $(FT_PRINTF) $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

# Compile .c files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile executables and link with ft_printf & libft
$(NAME_CLIENT): $(OBJS_CLIENT) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(FT_PRINTF) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(FT_PRINTF) $(LIBFT) -o $(NAME_SERVER)

# Compile ft_printf
$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

# Compile libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	make -C $(FT_PRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(FT_PRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
