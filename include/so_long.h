/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:15:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/18 12:47:35 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_WIDTH 32
# define TILE_HEIGHT 32

# include "../libs/mlx_linux/mlx.h"
# include "../libs/libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef enum e_tile_type
{
	EMPTY = '0',
	PLAYER = 'P'
}	t_tile_type;

typedef enum e_key_code
{
	ESC = XK_Escape,
	RIGHT_KEY = XK_Right,
	LEFT_KEY = XK_Left,
	UP_KEY = XK_Up,
	DOWN_KEY = XK_Down
}	t_key_code;

typedef enum e_close_status
{
	CLOSE_SUCCESS,
	CLOSE_FAILURE
}	t_close_status;

typedef struct s_tile
{
	void				*image;
	int					x_grid;
	int					y_grid;
	t_tile_type			type;
	struct s_tile		*right_tile;
	struct s_tile		*left_tile;
	struct s_tile		*up_tile;
	struct s_tile		*down_tile;
}	t_tile;

typedef struct s_player
{
	t_tile	*tile;
}	t_player;

typedef struct s_images
{
	void	*player;
	void	*background;
	void	*wall;
}	t_images;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*window;
	int				tile_width;
	int				tile_height;
	int				pixel_width;
	int				pixel_height;
	t_images		images;
	t_player		player;
	t_tile			***grid;
}	t_game;

int		close_game(char *message, t_game *game, t_close_status status);
int		key_press(int key, t_game *game);
void	*image_creation(t_game *game, t_tile *new_tile);
void	new_tile_coordinates(t_game *game, t_tile *tile, int x, int y);
void	ft_full_grid_clean(t_game *game);
void	tiles_coordinates(t_game *game);

#endif

// typedef struct s_image
// {
// 	void*	image_ptr;
// 	char*	address;
// 	int		bits_per_pixel;
// 	int		bytes_per_pixel;
// 	int		line_lenght;
// 	int		endian;
// } t_image;