/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:15:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:56 by lmeneghe         ###   ########.fr       */
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

typedef struct s_image
{
	void*	image_ptr;
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

// typedef struct s_tile t_tile; //Is this really necessary?

typedef struct s_tile
{
	t_image				*image;
	int					x_grid;
	int					y_grid;
	t_tile_type			type;
	struct s_tile		*right_tile; 
	struct s_tile		*left_tile;
	struct s_tile		*up_tile;
	struct s_tile		*down_tile;
} t_tile;

//Why s_tile instead of t_tile? I know it give errors, but why?
//off topic anotar cena de grid*** porque os valores por si só são *t_tile

typedef struct s_player
{
	t_tile	*tile;
} t_player;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*window;
	int				tile_width;
	int				tile_height;
	int				pixel_width;
	int				pixel_height;
	t_player		player; //review again why cant be a poiunter
	t_tile			***grid; //understand this shit better
} t_game;

enum key_code //Understand this shit better
{
	ESC = XK_Escape,
	RIGHT_KEY = XK_Right,
	LEFT_KEY = XK_Left,
	UP_KEY = XK_Up,
	DOWN_KEY = XK_Down
};

typedef enum
{
	CLOSE_SUCCESS,
	CLOSE_FAILURE
} close_status;

int		close_game(char *message, t_game *game, close_status status);
int		key_press(int key, t_game* game);
void*	image_creation(t_game* game, t_tile* new_tile);
void	new_tile_coordinates(t_game *game, t_tile *tile, int x, int y);
void	ft_full_grid_clean(t_game *game);
void	tiles_coordinates(t_game *game);

#endif