/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 09:09:11 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		close_game("Error\nError on player_move call", game, CLOSE_FAILURE);
	if (new_pos->type == WALL)
		return ;
    if (game->player.movements == INT_MAX)
		close_game("Error\nMaximum number of movements reached\n", game, CLOSE_OTHERS);
	old_pos->type = EMPTY;
	new_pos->type = PLAYER;
	game->player.tile = new_pos;
	new_pos->image = game->images.player;
	old_pos->image = game->images.background;
	mlx_put_image_to_window(game->mlx_ptr, game->window, game->images.background, \
	((old_pos->x_grid) * TILE_WIDTH), ((old_pos->y_grid) * TILE_HEIGHT));
	mlx_put_image_to_window(game->mlx_ptr, game->window, game->images.player, \
	((new_pos->x_grid) * TILE_WIDTH), ((new_pos->y_grid) * TILE_HEIGHT));
	game->player.movements++;
	ft_printf("Current number of movements is %i\n", game->player.movements);
}

int	key_press(int key, t_game *game)
{
	t_tile	*player_tile;

	if (!game)
		close_game("Error\nError on key_press call", NULL, CLOSE_OTHERS);
	player_tile = game->player.tile;
	if (key == ESC)
		close_game(NULL, game, CLOSE_SUCCESS);
	else if (key == RIGHT_KEY)
		player_move(game, player_tile, player_tile->right_tile);
	else if (key == LEFT_KEY)
		player_move(game, player_tile, player_tile->left_tile);
	else if (key == UP_KEY)
		player_move(game, player_tile, player_tile->up_tile);
	else if (key == DOWN_KEY)
		player_move(game, player_tile, player_tile->down_tile);
	else
		return (0);
	return (1);
}
