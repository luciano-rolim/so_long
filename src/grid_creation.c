/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:32:23 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 10:56:52 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static t_tile	*tile_creation(t_game *game, int x, int y, t_tile ***grid)
{
	t_tile		*new_tile;

	if (!game || !grid)
		end_game("Error\nError on tile_creation call", game, CLOSE_OTHER);
	new_tile = ft_calloc(1, sizeof(t_tile));
	if (!new_tile)
		end_game("Error\nft_calloc failure on tile", game, CLOSE_FAIL);
	new_tile->image = NULL;
	new_tile->right_tile = NULL;
	new_tile->left_tile = NULL;
	new_tile->up_tile = NULL;
	new_tile->down_tile = NULL;
	new_tile->x_grid = x;
	new_tile->y_grid = y;
	new_tile->checked = 0;
	return (new_tile);
}

static void	grid_allocation(t_game *game)
{
	int		y;

	if (!game)
		end_game("Error\nError on grid allocation call", NULL, CLOSE_OTHER);
	game->map.grid = ft_calloc(game->map.vertical_tiles, sizeof(t_tile *));
	if (!game->map.grid)
		end_game("Error\nft_calloc failure on grid", game, CLOSE_FAIL);
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		game->map.grid[y] = ft_calloc(game->map.horiz_tiles, sizeof(t_tile *));
		if (!game->map.grid[y])
			end_game("Error\nft_calloc fail - grid line", game, CLOSE_FAIL);
		y++;
	}
}

void	grid_creation(t_game *game)
{
	int		x;
	int		y;

	if (!game)
		end_game("Error\nError on grid_creation call", NULL, CLOSE_OTHER);
	grid_allocation(game);
	x = 0;
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		x = 0;
		while (x < game->map.horiz_tiles)
		{
			game->map.grid[y][x] = tile_creation(game, x, y, game->map.grid);
			x++;
		}
		y++;
	}
	tile_completion(game);
}
