/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 10:28:03 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_tile *tile_creation(t_game *game, int x, int y, t_tile ***grid)
{
	t_tile		*new_tile;

	if (!game || !grid)
		close_game("Error\nError on tile_creation call", game, CLOSE_OTHERS);
	new_tile = NULL;
	new_tile = ft_calloc(1, sizeof(t_tile));
	if (!new_tile)
		close_game("Error\nft_calloc failure on tile", game, CLOSE_FAILURE);
	new_tile->image = NULL;
	new_tile->right_tile = NULL;
	new_tile->left_tile = NULL;
	new_tile->up_tile = NULL;
	new_tile->down_tile = NULL;
	new_tile->x_grid = x;
	new_tile->y_grid = y;
	return (new_tile);
}

void	image_attribution(t_game *game, t_tile *tile)
{
	if (!game || !tile)
		close_game("Error\nError on image_attribution call", game, CLOSE_OTHERS);
	if (tile->type == PLAYER)
	{
		tile->image = game->images.player;
		game->player.tile = tile;
		game->player.movements = 0;
	}
	else if (tile->type == EMPTY)
		tile->image = game->images.background;
	else if (tile->type == WALL)
		tile->image = game->images.wall;
	else
		close_game("Error\nInvalid tile->image type", game, CLOSE_OTHERS);
}

void	tiles_coordinates(t_game *game)
{
	t_tile	*tmp_tile;
	int		x;
	int		y;
	int		i;
	t_line	*tmp_line;

	if (!game)
		close_game("Error\nError on tile_coordinates call", NULL, CLOSE_OTHERS);
	tmp_line = game->map.list; //Check if this is necessary
	tmp_tile = NULL; //Check if this is necessary
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		i = 0;
		x = 0;
		while (x < game->map.horizontal_tiles)
		{
			tmp_tile = game->map.grid[y][x];
			tmp_tile->type = tmp_line->content[i];
			image_attribution(game, tmp_tile);
			if (x < (game->map.horizontal_tiles - 1))
				tmp_tile->right_tile = game->map.grid[y][x + 1];
			if (x > 0)
				tmp_tile->left_tile = game->map.grid[y][x - 1];
			if (y > 0)
				tmp_tile->up_tile = game->map.grid[y - 1][x];
			if (y < (game->map.vertical_tiles - 1))
				tmp_tile->down_tile = game->map.grid[y + 1][x];
			mlx_put_image_to_window(game->mlx_ptr, game->window, tmp_tile->image, \
			tmp_tile->x_grid * TILE_WIDTH, tmp_tile->y_grid * TILE_HEIGHT);
			x++;
			i++;
		}
		tmp_line = tmp_line->next_line;
		y++;
	}
}

void	grid_allocation(t_game *game)
{
	int		y;

	if (!game)
		close_game("Error\nError on grid allocation call", NULL, CLOSE_OTHERS);
	game->map.grid = ft_calloc(game->map.vertical_tiles, sizeof(t_tile*));
	if (!game->map.grid)
		close_game("Error\nft_calloc failure on grid", game, CLOSE_FAILURE);
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		game->map.grid[y] = ft_calloc(game->map.horizontal_tiles, sizeof(t_tile*));
		if (!game->map.grid[y])
			close_game("Error\nft_calloc failure on grid line", game, CLOSE_FAILURE);
		y++;
	}
}

void	grid_creation(t_game *game)
{
	int		x;
	int		y;

	if (!game)
		close_game("Error\nError on grid_creation call", NULL, CLOSE_OTHERS);
	grid_allocation(game);
	x = 0;
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		x = 0;
		while (x < game->map.horizontal_tiles)
		{
			game->map.grid[y][x] = tile_creation(game, x, y, game->map.grid);
			x++;
		}
		y++;
	}
	tiles_coordinates(game);
}

void	start_graphics(t_game *game)
{
	if (!game)
		close_game("Error\nError on start_graphics call", NULL, CLOSE_OTHERS);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		close_game("Error\nError starting MLX connection", game, CLOSE_FAILURE);
	game->map.total_pixel_width = (TILE_WIDTH * game->map.horizontal_tiles);
	game->map.total_pixel_height = (TILE_HEIGHT * game->map.vertical_tiles);
	game->window = mlx_new_window(game->mlx_ptr, game->map.total_pixel_width, game->map.total_pixel_height, "Custom Pac-Man");
	if (!game->window)
		close_game("Error\nError initializing game window", game, CLOSE_FAILURE);
}

int	xpm_conversion(void **image, char* address, t_game *game)
{
    int img_width = TILE_WIDTH;
    int img_height = TILE_HEIGHT;

	if (!image || !address || !game)
		close_game("Error\nError on xpm_conversion call", game, CLOSE_FAILURE);
	*image = mlx_xpm_file_to_image(game->mlx_ptr, address, &img_width, &img_height);
	if (!image)
		return (0);
	return (1);
}

void	start_images(t_game *game)
{
	char* message;

	if (!game)
		close_game("Error\nError on start_images call", NULL, CLOSE_OTHERS);
	message = "Error initializing image";
	if (!xpm_conversion(&game->images.player, "assets/left_1.xpm", game))
		close_game(message, game, CLOSE_FAILURE);
	if (!xpm_conversion(&game->images.background, "assets/background.xpm", game))
		close_game("Error\nError initializing image", game, CLOSE_FAILURE);
	if (!xpm_conversion(&game->images.wall, "assets/wall.xpm", game))
		close_game("Error\nError initializing image", game, CLOSE_FAILURE);
}

int	check_extension(char *filename)
{
	char	*extension;

	if (!filename)
		return (0);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strlen(extension) != 4)
		return (0);
	if(ft_strncmp(extension, ".ber", 4))
		return (0);
	return (1);
}

void structs_initialization(t_game *game)
{
	game->mlx_ptr = NULL;
	game->window = NULL;
	game->player.tile = NULL;
	game->player.movements = 0;
	game->images.player = NULL;
	game->images.background = NULL;
	game->images.wall = NULL;
	game->map.types = "01P";
	game->map.grid = NULL;
	game->map.list = NULL;
	game->tmp_var.buffer = NULL;
	game->tmp_var.file_fd = -1;
	game->tmp_var.line_count = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !argv || !argv[0] || !argv[1])
		close_game("Error\nInvalid game arguments", NULL, CLOSE_OTHERS);
	if (!check_extension(argv[1]))
		close_game("Error\nMap file must be .ber type", NULL, CLOSE_OTHERS);
	structs_initialization(&game);
	build_map(&game, argv[1]);
	start_graphics(&game);
	start_images(&game);
	grid_creation(&game);
	mlx_key_hook(game.window, key_press, &game);
	mlx_loop(game.mlx_ptr);
	close_game(NULL, &game, CLOSE_SUCCESS);
}
