# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 16:56:17 by aelaaser          #+#    #+#              #
#    Updated: 2024/12/05 21:10:50 by aelaaser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Source files
SRCS = 	exit_utils.c get_next_line.c pixel_utils.c fdf.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
# Library name
NAME = fdf

# Default target
all: $(NAME)

# Rule to create the static library
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

# Ensure libft is built first
$(LIBFT):
	make -C libft

# Clean up build files
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
