/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:15:37 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/24 10:38:15 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_WIDTH 32
# define TILE_HEIGHT 32

//Custom libraries
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/get_next_line/get_next_line.h"

//MLX and X11 libraries
# include "../libs/mlx_linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

//C libraries
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

typedef enum e_tile_type
{
	PLAYER = 'P',
	EMPTY = '0',
	WALL = '1',
	COLLECTIBLE = 'C',
	EXIT = 'E',
	EXIT_AND_PLAYER
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
	CLOSE_FAILURE,
	CLOSE_OTHERS
}	t_close_status;

typedef struct s_tmp_var
{
	char			*buffer;
	int				file_fd;
	int				line_count;
	int				exit_found;
	int				collectables_found;
} t_tmp_var;

typedef struct s_line
{
	char			*content;
	struct s_line	*next_line;
} t_line;

typedef struct s_tile
{
	void				*image;
	int					x_grid;
	int					y_grid;
	int					checked;
	t_tile_type			type;
	struct s_tile		*right_tile;
	struct s_tile		*left_tile;
	struct s_tile		*up_tile;
	struct s_tile		*down_tile;
}	t_tile;

typedef struct s_player
{
	t_tile		*tile;
	int			movements;
}	t_player;

typedef struct s_images
{
	void	*player;
	void	*background;
	void	*wall;
	void	*exit;
	void	*collectible;
	void	*exit_and_player;
}	t_images;

typedef struct s_map
{
	int				horizontal_tiles;
	int				vertical_tiles;
	int				total_pixel_width;
	int				total_pixel_height;
	int				collectibles;
	char			*types;
	t_tile			***grid;
	t_line			*list;
}	t_map;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*window;
	int				key_states[256];
	t_map			map;
	t_images		images;
	t_player		player;
	t_tmp_var		tmp_var;
}	t_game;

//General functions
void	close_game(char *message, t_game *game, t_close_status status);
int		exit_program(char *message, t_close_status status);
void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos);

//Map functions
void	build_map(t_game *game, char *filename);
void	handle_line_error(char *message, t_game *game, char *buffer, int file_fd);
void	additional_map_checks(t_game *game, char *buffer, int file_fd);
void	clean_buffer_fd_gnl(char* buffer, int file_fd, t_game *game);

//Grid and tiles creation
void	grid_creation(t_game *game);
void	tile_completion(t_game *game);

//Images functiosn
void	start_images(t_game *game);
void	fill_screen(t_game *game);

//Node functions
void	add_new_node(t_game *game, char *content);
t_line *last_node(t_game *game, t_line *head_node);

//Generic utils
void	put_image(t_game *game, void *image, int x, int y);
void	search_valid_path(t_game *game, t_tile *current_tile);

//Handler functions
int		key_press_handler(int key, t_game *game);
int		mouse_close_handler(t_game *game);

#endif