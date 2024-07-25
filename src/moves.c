/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 11:04:24 by lmeneghe         ###   ########.fr       */
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

static void	adjust_images(t_game *game, t_tile *old_pos, void *old_image, t_tile *new_pos, void *new_image)
{
	if (!old_pos || !old_image || !new_pos || !new_image)
		end_game("Error\nError on adjust_images call", game, CLOSE_OTHER);
	new_pos->image = new_image;
	old_pos->image = old_image;
}

static void	move_type(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		end_game("Error\nError on move_type call", game, CLOSE_FAIL);
	if (new_pos->type == EXIT)
	{
		adjust_images(game, old_pos, game->images.background, new_pos, game->images.exit_player);
		if (game->map.collectibles == 0)
		{
			make_move(game, old_pos, new_pos);
			ft_printf("You won!\n");
			end_game(NULL, game, CLOSE_SUCCESS);
		}
	}
	else if (old_pos->type == EXIT)
		adjust_images(game, old_pos, game->images.exit, new_pos, game->images.player);
	else if (new_pos->type == EMPTY || new_pos->type == COLLECTIBLE)
	{
		if (new_pos->type == COLLECTIBLE)
		{
			game->map.collectibles--;
			new_pos->type = EMPTY;
		}
		adjust_images(game, old_pos, game->images.background, new_pos, game->images.player);
	}
	make_move(game, old_pos, new_pos);
}

void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		end_game("Error\nError on player_move call", game, CLOSE_FAIL);
    if (game->player.movements == INT_MAX)
		end_game("Error\nMaximum number of movements reached\n", game, CLOSE_OTHER);
	if (new_pos == game->player.tile)
		end_game("Error\nDuplicate player tile\n", game, CLOSE_OTHER);
	if (new_pos->type == WALL)
		return ;
	move_type(game, old_pos, new_pos);
}
