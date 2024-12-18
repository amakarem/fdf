# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 16:56:17 by aelaaser          #+#    #+#              #
#    Updated: 2024/12/18 14:33:53 by aelaaser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Determine OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    MLX_DIR = minilibx_macos
else
    MLX_DIR = minilibx_linux
endif


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(MLX_DIR)

# Source files
SRCS = exit_utils.c get_next_line.c pixel_utils.c draw.c fdf_utils.c fdf.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = libft/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Library name
NAME = fdf

# Default target
all: $(NAME)

# Rule to create the static library
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -L$(MLX_DIR) -framework OpenGL -framework AppKit -o $(NAME)

# # Rule to compile .c to .o
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I$(MLX_DIR) -c $< -o $@

# Ensure libft is built first
$(LIBFT):
	make -C libft

# Ensure mlx is built first
$(MLX):
	make -C $(MLX_DIR)	

# Clean up build files
clean:
	rm -f $(OBJS)
	make clean -C libft
	make clean -C $(MLX_DIR)

# Remove all build files (including executable)
fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make clean -C $(MLX_DIR)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
