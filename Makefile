# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 12:12:03 by lmeneghe          #+#    #+#              #
#    Updated: 2024/07/25 09:02:01 by lmeneghe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME            = so_long

# Lib Directories
LIBFT_DIR       	= ./libs/libft/
PRINTF_DIR      	= ./libs/ft_printf/
GET_NEXT_LINE_DIR	= ./libs/get_next_line/
MLX_DIR				= ./libs/mlx_linux/

# Compiler and Flags
CC              = gcc
CFLAGS          = #-Wall -Wextra -Werror 

#REMEMBER TO PUT THE FLAGS BACK LATER

# Library files
LIBFT           = $(LIBFT_DIR)libft.a
PRINTF          = $(PRINTF_DIR)libprintf.a
GET_NEXT_LINE	= $(GET_NEXT_LINE_DIR)libgnl.a
MLX				= $(MLX_DIR)libmlx_Linux.a

# MLX associated Libs required for program compilation 
MLX_LIBS       = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lz -lm

# Source Files
SRC_FILES       =	src/main.c src/moves.c src/cleaning.c src/build_map.c src/build_map_utils.c \
					src/node_functions.c src/grid_creation.c src/grid_tile_creation.c src/images.c \
					src/generic_utils.c src/handlers.c

# Object files
OBJS_DIR        = obj/
OBJS            = $(SRC_FILES:src/%.c=$(OBJS_DIR)%.o)

$(MLX_DIR):
				git clone https://github.com/42Paris/minilibx-linux $(MLX_DIR)
				$(MAKE) -C $(MLX_DIR)

# Main rule: compile libraries and then the program.
$(NAME):		$(MLX) $(OBJS) $(LIBFT) $(PRINTF) $(GET_NEXT_LINE)
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft \
				-L$(PRINTF_DIR) -lprintf -L$(GET_NEXT_LINE_DIR) -lgnl \
				$(MLX_LIBS) -o $(NAME)

# Command to execute make inside libft folder and generate libft.a file
$(LIBFT):
				@make -C $(LIBFT_DIR)

# Command to execute make inside printf folder and generate libprintf.a file
$(PRINTF):
				@make -C $(PRINTF_DIR)

# Command to execute make inside GNL folder and generate libgnl.a file
$(GET_NEXT_LINE):
				@make -C $(GET_NEXT_LINE_DIR)

# Command to execute make inside mlx folder and generate libmlx.a file
$(MLX):			$(MLX_DIR)
				@$(MAKE) -C $(MLX_DIR)

# Make instruction on how to compile .o if is not up to date
$(OBJS_DIR)%.o: src/%.c
				@mkdir -p $(OBJS_DIR)
				@$(CC) $(CFLAGS) -O3 -c $< -o $@

# Standard all command
all:            $(NAME)

# Clean: removes all .o files in all directories
clean:
				@find $(OBJS_DIR) -type f -name "*.o" -delete
				@make clean -C $(LIBFT_DIR)
				@make clean -C $(PRINTF_DIR)
				@make clean -C $(GET_NEXT_LINE_DIR)
				@if [ -d "$(MLX_DIR)" ]; then find $(MLX_DIR) \
				-type f -name "*.o" -delete; fi

# Fclean: call clean + remove so_long file
# Extra rule to fclean the libft and printf libraries + clean mlx library
fclean:         clean
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@make fclean -C $(PRINTF_DIR)
				@make fclean -C $(GET_NEXT_LINE_DIR)
				@if [ -d "$(MLX_DIR)" ]; then make clean -C $(MLX_DIR); fi
#				@make clean -C $(MLX_DIR)

# Standard re command
re:             fclean all

# Standard .PHONY protection
.PHONY:         all clean fclean re setup_mlx

# Ensure "make" command behave as "make all"
.DEFAULT_GOAL := all
