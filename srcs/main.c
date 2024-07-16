/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/16 09:42:55 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	my_pixel_put(t_image* image, int x_axis, int y_axis, unsigned int color)
{
	char	*pixel;

	pixel = NULL;
	pixel = image->address;
	pixel += y_axis * image->line_lenght; 
	pixel += x_axis * image->bytes_per_pixel;
	*(unsigned int *)pixel = color;
}

void pixel_fill(t_image* image, t_game* game, t_tile* new_tile)
{
	int				x_axis;
	int				y_axis;
	unsigned int	color;

	if (new_tile->type == '0')
		color = 0x00FFFFFF;
	else if (new_tile->type == 'P')
		color = 0x00FF0000;
	y_axis = 0;
	while (y_axis < TILE_HEIGHT)
	{
		x_axis = 0;
		while (x_axis < TILE_WIDTH)
		{
			my_pixel_put(image, x_axis, y_axis, color);
			x_axis++;
		}
		y_axis++;
	}
}

void* image_creation(t_game* game, t_tile* new_tile)
{
	t_image	new_image;
	int		bytes_per_pixel;

	new_image.image = mlx_new_image(game->mlx_connection, TILE_WIDTH, TILE_HEIGHT);
	if (!new_image.image)
		close_game_failure(game, NULL);
	new_image.address = mlx_get_data_addr(new_image.image, &new_image.bits_per_pixel, &new_image.line_lenght, &new_image.endian);
	if (!new_image.address)
		close_game_failure(game, new_image.image);
	new_image.bytes_per_pixel = (new_image.bits_per_pixel / 8);
	pixel_fill(&new_image, game, new_tile);
	return (new_image.image);
}

t_tile	tile_creation(t_game* game, int x, int y)
{
	t_tile*		new_tile;
	// t_player	player;

	new_tile = malloc(sizeof(t_tile));
	new_tile->x_grid = x + 1;
	new_tile->y_grid = y + 1;

	if (new_tile->x_grid == 1 && new_tile->y_grid == 1)
	{
		// player.tile = &new_tile;
		new_tile->type = 'P';
	}
	else
		new_tile->type = '0';
	new_tile->image = image_creation(game, new_tile);
	mlx_put_image_to_window(game->mlx_connection, game->window, new_tile->image, x * TILE_WIDTH, y * TILE_HEIGHT);
	return (*new_tile);
}

t_tile** grid_allocation(t_game* game, t_tile** grid)
{
	int y;

	grid = malloc(sizeof(t_tile*) * (game->height_tile_size));
	y = 0;
	while (y < game->height_tile_size)
	{
		grid[y] = malloc(sizeof(t_tile*) * (game->width_tile_size));
		y++;
	}
	return (grid);
}

void grid_creation(t_game* game)
{
	t_tile	**grid;
	int		x;
	int		y;

	grid = grid_allocation(game, grid);
	x = 0;
	y = 0;
	while (y < game->height_tile_size)
	{
		x = 0;
		while (x < game->width_tile_size)
		{
			grid[y][x] = tile_creation(game, x, y);
			x++;
		}
		y++;
	}
}

int	main (int argc, char **argv)
{
	//int	check_errors; map, argc, argv, etc.
	t_game	game;

	// if (argc != 2)
	// 	return (EXIT_FAILURE);
	game.mlx_connection = mlx_init();
	if (!game.mlx_connection)
		return (EXIT_FAILURE);
	game.width_tile_size = 10;
	game.height_tile_size = 10;
	game.pixel_widht = (TILE_WIDTH * game.width_tile_size);
	game.pixel_height = (TILE_HEIGHT * game.height_tile_size);
	game.window = mlx_new_window(game.mlx_connection, game.pixel_widht, game.pixel_height, "Custom Pac-Man");
	if (!game.window)
		close_game_failure(&game, NULL);
	grid_creation(&game);
	// mlx_key_hook(game.window, key_press, &game);
	mlx_loop(game.mlx_connection);
}

/*

Objectives:
1 - Initialize connection, window, etc.
2 - Put some shit on screen
3 - On ESC key, close program
4 - 
5 - 

Backlog: 
- Map and map structure
- Player
- Collectibles
- Usar mlx_get_screen_size para entender melhor como estruturar a parada, sepa jogo do tamanho da tela?
- mlx_hook(game.window, DestroyNotify, StructureNotifyMask, close_game_success, &game);
- If game is too much big for the current screen, display error
- Game file must be compatible with the map size. If map is 10 x 5, then stuff should be 10 x 64 (640) and 5 x 64 (320)

*/

/*

// /* Allocates memory to save a tilemap with same size as <map> */
// t_tile	**alloc_tilemap(char **map)
// {
// 	t_tile	**tilemap;
// 	int		i;

// 	tilemap = malloc(sizeof(t_tile *) * ft_chartable_linecount(map) + 1);
// 	if (tilemap == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (map[i] != NULL)
// 	{
// 		tilemap[i] = malloc(sizeof(t_tile) * ft_strlen(*map) + 1);
// 		if (tilemap == NULL)
// 		{
// 			while (i > 0)
// 				free(tilemap[--i]);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (tilemap);
// }
