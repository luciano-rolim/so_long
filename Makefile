# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 12:12:03 by lmeneghe          #+#    #+#              #
#    Updated: 2024/07/11 14:11:57 by lmeneghe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME            = so_long

# Lib Directories
LIBFT_DIR       = ./libs/libft/
PRINTF_DIR      = ./libs/ft_printf/
MLX_DIR         = ./libs/mlx_linux/

# Compiler and Flags
CC              = gcc
CFLAGS          = #-Wall -Wextra -Werror 

#REMEMBER TO PUT THE FLAGS BACK LATER

# Library files
LIBFT           = $(LIBFT_DIR)libft.a
PRINTF          = $(PRINTF_DIR)libprintf.a
MLX				= $(MLX_DIR)libmlx_Linux.a

# MLX associated Libs required for program compilation 
MLX_LIBS       = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lz -lm

# Source Files
SRC_FILES       = srcs/main.c

# Object files
OBJS_DIR        = objs/
OBJS            = $(SRC_FILES:srcs/%.c=$(OBJS_DIR)%.o)

# Setup mlx_linux if it doesn't exist, wifh fi control to mark end of the condition
setup_mlx:
				@if [ ! -d "$(MLX_DIR)" ]; then \
					git clone https://github.com/42Paris/minilibx-linux $(MLX_DIR); \
				fi

# Main rule: compile libraries and then the program.
$(NAME):		setup_mlx $(MLX) $(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft \
				-L$(PRINTF_DIR) -lprintf $(MLX_LIBS) -o $(NAME)

# Command to execute make inside libft folder and generate libft.a file
$(LIBFT):
				@make -C $(LIBFT_DIR)

# Command to execute make inside printf folder and generate libprintf.a file
$(PRINTF):
				@make -C $(PRINTF_DIR)

# Command to execute make inside mlx folder and generate libmlx.a file
$(MLX):
				@make -C $(MLX_DIR)

# Make instruction on how to compile .o if is not up to date
$(OBJS_DIR)%.o: srcs/%.c
				@mkdir -p $(OBJS_DIR)
				@$(CC) $(CFLAGS) -O3 -c $< -o $@

# Standard all command
all:            $(NAME)

# Clean: removes all .o files in all directories
clean:
				@find $(OBJS_DIR) -type f -name "*.o" -delete

# Fclean: call clean + remove so_long file
# Extra rule to fclean the libft and printf libraries + clean mlx library
fclean:         clean
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@make fclean -C $(PRINTF_DIR)
				@make clean -C $(MLX_DIR)

# Standard re command
re:             fclean all

# Standard .PHONY protection
.PHONY:         all clean fclean re setup_mlx

# Ensure "make" command behave as "make all"
.DEFAULT_GOAL := all
