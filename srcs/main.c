/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/17 16:04:32 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	pixel_put(t_image *image, int x_axis, int y_axis, unsigned int color)
{
	char	*pixel;

	if (!image)
		close_game("Error on pixel_put call", NULL, CLOSE_FAILURE);
	pixel = NULL;
	pixel = image->address;
	pixel += y_axis * image->line_lenght;
	pixel += x_axis * image->bytes_per_pixel;
	*(unsigned int *)pixel = color;
}

void	pixel_fill(t_image *image, t_game *game, t_tile *new_tile)
{
	int				x_axis;
	int				y_axis;
	unsigned int	color;

	if (!image || !game || !new_tile)
		close_game("Error on pixel_fill call", NULL, CLOSE_FAILURE);
	if (new_tile->type == '0') //Check how to properly handle this later
		color = 0x00FFFFFF;
	else
		color = 0x00FF0000;
	y_axis = 0;
	while (y_axis < TILE_HEIGHT)
	{
		x_axis = 0;
		while (x_axis < TILE_WIDTH)
		{
			pixel_put(image, x_axis, y_axis, color);
			x_axis++;
		}
		y_axis++;
	}
}

void	*image_creation(t_game *game, t_tile *new_tile)
{
	t_image	new_image;

	if (!game || !new_tile)
		close_game("Error on image_creation call", NULL, CLOSE_FAILURE);
	new_image.image_ptr = NULL;
	new_image.address = NULL;
	new_image.image_ptr = mlx_new_image(game->mlx_ptr, TILE_WIDTH, TILE_HEIGHT);
	if (!new_image.image_ptr)
		close_game("Failure creating new img", game, CLOSE_FAILURE);
	new_image.address = mlx_get_data_addr(new_image.image_ptr, &new_image.bits_per_pixel, &new_image.line_lenght, &new_image.endian);
	if (!new_image.address)
		close_game("Failure creating img address", game, CLOSE_FAILURE);
	new_image.bytes_per_pixel = (new_image.bits_per_pixel / 8);
	pixel_fill(&new_image, game, new_tile);
	return (new_image.image_ptr);
}

t_tile *tile_creation(t_game *game, int x, int y, t_tile ***grid)
{
	t_tile		*new_tile;

	if (!game || !grid)
		close_game("Error on tile_creation call", NULL, CLOSE_FAILURE);
	new_tile = NULL;
	new_tile = ft_calloc(1, sizeof(t_tile));
	if (!new_tile)
		close_game("ft_calloc failure on tile", game, CLOSE_FAILURE);
	new_tile->image = NULL;
	new_tile->right_tile = NULL;
	new_tile->left_tile = NULL;
	new_tile->up_tile = NULL;
	new_tile->down_tile = NULL;
	new_tile->x_grid = x;
	new_tile->y_grid = y;
	if (new_tile->x_grid == 0 && new_tile->y_grid == 0) //Temporary code while we dont have a map
	{
		new_tile->type = 'P';
		game->player.tile = new_tile;
	}
	else
		new_tile->type = '0';
	new_tile->image = image_creation(game, new_tile);
	mlx_put_image_to_window(game->mlx_ptr, game->window, new_tile->image, x * TILE_WIDTH, y * TILE_HEIGHT);
	return (new_tile);
}

void	tiles_coordinates(t_game *game)
{
	t_tile	*tmp;
	int		x;
	int		y;

	if (!game)
		close_game("Error on tile_coordinates call", NULL, CLOSE_FAILURE);
	tmp = NULL;
	y = 0;
	while (y < game->tile_height)
	{
		x = 0;
		while (x < game->tile_width)
		{
			tmp = game->grid[y][x];
			if (x < (game->tile_width - 1))
				tmp->right_tile = game->grid[y][x + 1];
			if (x > 0)
				tmp->left_tile = game->grid[y][x - 1];
			if (y > 0)
				tmp->up_tile = game->grid[y - 1][x];
			if (y < (game->tile_height - 1))
				tmp->down_tile = game->grid[y + 1][x];
			x++;
		}
		y++;
	}
}

t_tile	***grid_allocation(t_game *game)
{
	int		y;

	if (!game)
		close_game("Error on grid allocation call", NULL, CLOSE_FAILURE);
	game->grid = ft_calloc(game->tile_height, sizeof(t_tile*));
	if (!game->grid)
		close_game("ft_calloc failure on grid", game, CLOSE_FAILURE);
	y = 0;
	while (y < game->tile_height)
	{
		game->grid[y] = ft_calloc(game->tile_width, sizeof(t_tile*));
		if (!game->grid[y])
			close_game("ft_calloc failure on grid line", game, CLOSE_FAILURE);
		y++;
	}
	return (game->grid);
}

void	grid_creation(t_game *game)
{
	int		x;
	int		y;

	if (!game)
		close_game("Error on grid_creation call", NULL, CLOSE_FAILURE);
	game->grid = grid_allocation(game);
	x = 0;
	y = 0;
	while (y < game->tile_height)
	{
		x = 0;
		while (x < game->tile_width)
		{
			game->grid[y][x] = tile_creation(game, x, y, game->grid);
			x++;
		}
		y++;
	}
	tiles_coordinates(game);
}

t_game	start_graphics(void)
{
	t_game	game;

	game.mlx_ptr = NULL;
	game.window = NULL;
	game.grid = NULL;
	game.player.tile = NULL;
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		close_game("Error starting MLX connection", NULL, CLOSE_FAILURE);
	game.tile_width = 10; //Temporary map size definition
	game.tile_height = 10; //Temporary map size definition
	game.pixel_width = (TILE_WIDTH * game.tile_width);
	game.pixel_height = (TILE_HEIGHT * game.tile_height);
	game.window = mlx_new_window(game.mlx_ptr, game.pixel_width, game.pixel_height, "Custom Pac-Man");
	if (!game.window)
		close_game("Error initializing game window", &game, CLOSE_FAILURE);
	return (game);
}

int	main(void)
{
	t_game	game;
	//Check pointers on argv and etc.

	game = start_graphics();
	grid_creation(&game);
	mlx_key_hook(game.window, key_press, &game);
	mlx_loop(game.mlx_ptr);
}
