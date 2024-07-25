/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 13:44:36 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	make_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	game->player.tile = new_pos;
	put_image(game, old_pos->image, old_pos->x_grid, old_pos->y_grid);
	put_image(game, new_pos->image, new_pos->x_grid, new_pos->y_grid);
	game->player.movements++;
	ft_printf("Current number of movements is %i\n", game->player.movements);
}

static void	adjust_img(t_game *game, t_tile *tile, void *new_img)
{
	if (!game || !tile || !new_img)
		end_game("Error\nError on adjust_img call", game, CLOSE_FAIL);
	tile->image = new_img;
}

static void	move_type(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		end_game("Error\nError on move_type call", game, CLOSE_FAIL);
	if (new_pos->type == EXIT)
	{
		adjust_img(game, old_pos, game->images.background);
		adjust_img(game, new_pos, game->images.exit_player);
		if (game->map.collectibles == 0)
		{
			make_move(game, old_pos, new_pos);
			ft_printf("You won!\n");
			end_game(NULL, game, CLOSE_SUCCESS);
		}
	}
	else if (old_pos->type == EXIT)
	{
		adjust_img(game, old_pos, game->images.exit);
		adjust_img(game, new_pos, game->images.player);
	}
	else if (new_pos->type == EMPTY || new_pos->type == COLLECTIBLE)
	{
		adjust_img(game, old_pos, game->images.background);
		adjust_img(game, new_pos, game->images.player);
	}
	make_move(game, old_pos, new_pos);
}

void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		end_game("Error\nError on player_move call", game, CLOSE_FAIL);
	if (game->player.movements == INT_MAX)
		end_game("Error\nMax number of movements reached\n", game, CLOSE_OTHER);
	if (new_pos == game->player.tile)
		end_game("Error\nDuplicate player tile\n", game, CLOSE_OTHER);
	if (new_pos->type == WALL)
		return ;
	if (new_pos->type == COLLECTIBLE)
	{
		game->map.collectibles--;
		new_pos->type = EMPTY;
	}
	move_type(game, old_pos, new_pos);
}
