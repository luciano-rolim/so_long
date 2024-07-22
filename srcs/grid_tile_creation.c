/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_tile_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:49:21 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 16:35:04 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	tile_image_attribution(t_game *game, t_tile *tile)
{
	if (!game || !tile)
		close_game("Error\nError on tile_image_attribution call", game, CLOSE_OTHERS);
	if (tile->type == PLAYER)
	{
		tile->image = game->images.player;
		game->player.tile = tile;
	}
	else if (tile->type == EMPTY)
		tile->image = game->images.background;
	else if (tile->type == WALL)
		tile->image = game->images.wall;
	else if (tile->type == EXIT)
		tile->image = game->images.exit;
	else if (tile->type == COLLECTIBLE)
		tile->image = game->images.collectible;
	else
		close_game("Error\nInvalid tile->image type", game, CLOSE_OTHERS);
}

static void	tile_coordinates(t_game *game, t_tile *tile, int x, int y)
{
	if (!game || !tile)
		close_game("Error\nError on tile_coordinates call", game, CLOSE_OTHERS);
	if (x < (game->map.horizontal_tiles - 1))
		tile->right_tile = game->map.grid[y][x + 1];
	if (x > 0)
		tile->left_tile = game->map.grid[y][x - 1];
	if (y > 0)
		tile->up_tile = game->map.grid[y - 1][x];
	if (y < (game->map.vertical_tiles - 1))
		tile->down_tile = game->map.grid[y + 1][x];	
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

static void	fill_tiles_information(t_game *game, t_line *tmp_line, int y)
{
	t_tile	*tmp_tile;
	int x;
	int	i;

	if (!game || !tmp_line)
		close_game("Error\nError on fill_tiles_information call", game, CLOSE_OTHERS);
	tmp_tile = NULL;
	x = 0;
	i = 0;
	while (x < game->map.horizontal_tiles)
	{
		tmp_tile = game->map.grid[y][x];
		tmp_tile->type = tmp_line->content[i];
		tile_image_attribution(game, tmp_tile);
		tile_coordinates(game, tmp_tile, x, y);
		x++;
		i++;
	}
}

void	tile_completion(t_game *game)
{
	int		y;
	t_line	*tmp_line;

	if (!game)
		close_game("Error\nError on tile_coordinates call", NULL, CLOSE_OTHERS);
	tmp_line = game->map.list;
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		fill_tiles_information(game, tmp_line, y);
		tmp_line = tmp_line->next_line;
		y++;
	}
	search_valid_path(game, game->player.tile);
	if (game->tmp_var.exit_found != 1 || (game->tmp_var.collectables_found != game->map.collectibles))
		close_game("Error\nPath is blocked", game, CLOSE_OTHERS);
}
