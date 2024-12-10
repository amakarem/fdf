# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 16:56:17 by aelaaser          #+#    #+#              #
#    Updated: 2024/12/10 20:13:10 by aelaaser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Source files
SRCS = exit_utils.c get_next_line.c pixel_utils.c draw.c fdf.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

# Library name
NAME = fdf

# Default target
all: $(NAME)

# Rule to create the static library
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# # Rule to compile .c to .o
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# Ensure libft is built first
$(LIBFT):
	make -C libft

# Ensure mlx is built first
$(MLX):
	make -C mlx	

# Clean up build files
clean:
	rm -f $(OBJS)
	make clean -C libft
	make clean -C mlx

# Remove all build files (including executable)
fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make clean -C mlx

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
