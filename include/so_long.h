/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:15:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/16 09:45:11 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_WIDTH 64
# define TILE_HEIGHT 64

# include "../libs/mlx_linux/mlx.h"
# include "../libs/libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_game
{
	void*			mlx_connection;
	void*			window;
	int				width_tile_size;
	int				height_tile_size;
	int				pixel_widht;
	int				pixel_height;
	int				size;
} t_game;

typedef struct s_image
{
	void*	image;
	char*	address;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		line_lenght;
	int		endian;
} t_image;


typedef enum e_tile_type //Understand this shit better
{
	EMPTY = '0',
	PLAYER = 'P'
} t_tile_type;

typedef struct s_tile
{
	t_image*	image;
	int			x_grid;
	int			y_grid;
	t_tile_type	type;
	t_tile		*right_tile;
	t_tile		*left_tile;
	t_tile		*up_tile;
	t_tile		*down_tile;
} t_tile;

typedef struct s_player
{
	t_tile	*tile;
} t_player;

enum key_code //Understand this shit better
{
	ESC = XK_Escape,
	RIGHT_KEY = XK_Right,
	LEFT_KEY = XK_Left,
	UP_KEY = XK_Up,
	DOWN_KEY = XK_Down
};

int		close_game_failure(t_game *game, t_image* image);
int		close_game_success(t_game *game);
int		key_press(int key, t_game* game);

#endif