/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:32:23 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 10:49:29 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static t_tile	*tile_creation(t_game *game, int x, int y, t_tile ***grid)
{
	t_tile		*new_tile;

	if (!game || !grid)
		close_game("Error\nError on tile_creation call", game, CLOSE_OTHERS);
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

static void	grid_allocation(t_game *game)
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
	tile_completion(game);
}
