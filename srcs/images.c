/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:52:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 16:37:57 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	xpm_conversion(void **image, char* address, t_game *game)
{
    int img_width;
    int img_height;

	if (!image || !address || !game)
		close_game("Error\nError on xpm_conversion call", game, CLOSE_OTHERS);
	img_width = TILE_WIDTH;
	img_height = TILE_HEIGHT;
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
	if (!xpm_conversion(&game->images.exit, "assets/exit.xpm", game))
		close_game("Error\nError initializing image", game, CLOSE_FAILURE);
	if (!xpm_conversion(&game->images.collectible, "assets/collectible.xpm", game))
		close_game("Error\nError initializing image", game, CLOSE_FAILURE);
	if (!xpm_conversion(&game->images.exit_and_player, "assets/exit_and_player.xpm", game))
		close_game("Error\nError initializing image", game, CLOSE_FAILURE);
}

static void	put_tiles_on_screen(t_game *game, int y)
{
	t_tile	*tmp_tile;
	int		x;

	if (!game)
		close_game("Error\nError on put_tiles_on_screen call", NULL, CLOSE_OTHERS);
	tmp_tile = NULL;
	x = 0;
	while (x < game->map.horizontal_tiles)
	{
		tmp_tile = game->map.grid[y][x];
		put_image(game, tmp_tile->image, tmp_tile->x_grid, tmp_tile->y_grid);
		x++;
	}
}

void	fill_screen(t_game *game)
{
	int y;

	if (!game)
		close_game("Error\nInvalid fill_screen function call", NULL, CLOSE_OTHERS);
	game->window = mlx_new_window(game->mlx_ptr, game->map.total_pixel_width, game->map.total_pixel_height, "Custom Pac-Man");
	if (!game->window)
		close_game("Error\nError initializing game window", game, CLOSE_FAILURE);
	y = -1;
	while (++y < game->map.vertical_tiles)
		put_tiles_on_screen(game, y);
}

