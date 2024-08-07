/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:52:22 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 11:04:24 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	xpm_conversion(void **image, char *address, t_game *game)
{
	int	img_width;
	int	img_height;

	if (!image || !address || !game)
		end_game("Error\nError on xpm_conversion call", game, CLOSE_OTHER);
	img_width = TILE_WIDTH;
	img_height = TILE_HEIGHT;
	*image = mlx_xpm_file_to_image(game->mlx_ptr, address, \
	&img_width, &img_height);
	if (!image)
		end_game("Error on xpm file conversion", game, CLOSE_FAIL);
}

void	start_images(t_game *game)
{
	xpm_conversion(&game->images.player, "textures/player.xpm", game);
	xpm_conversion(&game->images.background, "textures/background.xpm", game);
	xpm_conversion(&game->images.wall, "textures/wall.xpm", game);
	xpm_conversion(&game->images.exit, "textures/exit.xpm", game);
	xpm_conversion(&game->images.collectible, "textures/collectible.xpm", game);
	xpm_conversion(&game->images.exit_player, "textures/exit_player.xpm", game);
}

static void	put_tiles_on_screen(t_game *game, int y)
{
	t_tile	*tmp_tile;
	int		x;

	if (!game)
		end_game("Error\nError on put_tiles_on_screen call", NULL, CLOSE_OTHER);
	tmp_tile = NULL;
	x = 0;
	while (x < game->map.horiz_tiles)
	{
		tmp_tile = game->map.grid[y][x];
		put_image(game, tmp_tile->image, tmp_tile->x_grid, tmp_tile->y_grid);
		x++;
	}
}

void	fill_screen(t_game *game)
{
	int		screen_width;
	int		screen_height;
	int		max_width;
	int		max_height;
	int		y;

	if (!game)
		end_game("Error\nInvalid fill_screen function call", NULL, CLOSE_OTHER);
	max_width = (game->map.total_pixel_width + 96);
	max_height = (game->map.total_pixel_height + 96);
	mlx_get_screen_size(game->mlx_ptr, &screen_width, &screen_height);
	if (max_width > screen_width || max_height > screen_height)
		end_game("Error\nGame map is too big for screen", game, CLOSE_OTHER);
	game->window = mlx_new_window(game->mlx_ptr, game->map.total_pixel_width, \
	game->map.total_pixel_height, "Custom Pac-Man");
	if (!game->window)
		end_game("Error\nError initializing game window", game, CLOSE_FAIL);
	y = -1;
	while (++y < game->map.vertical_tiles)
		put_tiles_on_screen(game, y);
}
