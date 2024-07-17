/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/17 16:02:53 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	t_image	new_empty;
	t_image	new_player;

	if (!game || !old_pos || !new_pos)
		close_game("Error on player_move call", game, CLOSE_FAILURE);
	new_empty.image_ptr = NULL;
	new_empty.address = NULL;
	new_player.image_ptr = NULL;
	new_player.address = NULL;
	old_pos->type = '0';
	new_pos->type = 'P';
	game->player.tile = new_pos;
	new_empty.image_ptr = image_creation(game, old_pos);
	new_player.image_ptr = image_creation(game, new_pos);
	mlx_put_image_to_window(game->mlx_ptr, game->window, new_empty.image_ptr, \
	((old_pos->x_grid) * TILE_WIDTH), ((old_pos->y_grid) * TILE_HEIGHT));
	mlx_put_image_to_window(game->mlx_ptr, game->window, new_player.image_ptr, \
	((new_pos->x_grid) * TILE_WIDTH), ((new_pos->y_grid) * TILE_HEIGHT));
	mlx_destroy_image(game->mlx_ptr, old_pos->image);
	mlx_destroy_image(game->mlx_ptr, new_pos->image);
	old_pos->image = new_empty.image_ptr;
	new_pos->image = new_player.image_ptr;
}

int	key_press(int key, t_game *game)
{
	t_tile	*player_tile;

	if (!game)
		close_game("Error on key_press call", NULL, CLOSE_FAILURE);
	player_tile = NULL;
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
