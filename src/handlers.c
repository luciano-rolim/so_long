/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:45:29 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 10:56:52 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	mouse_close_handler(t_game *game)
{
	end_game("Game closed after 'x' was clicked", game, CLOSE_SUCCESS);
	return (0);
}

int	key_press_handler(int key, t_game *game)
{
	t_tile	*player_tile;

	if (!game)
		end_game("Error\nError on key_press call", NULL, CLOSE_OTHER);
	player_tile = game->player.tile;
	if (key == ESC)
		end_game("ESC key pressed - Game closed", game, CLOSE_SUCCESS);
	else if (key == RIGHT_KEY || key == EXTRA_RIGHT_KEY)
		player_move(game, player_tile, player_tile->right_tile);
	else if (key == LEFT_KEY || key == EXTRA_LEFT_KEY)
		player_move(game, player_tile, player_tile->left_tile);
	else if (key == UP_KEY || key == EXTRA_UP_KEY)
		player_move(game, player_tile, player_tile->up_tile);
	else if (key == DOWN_KEY || key == EXTRA_DOWN_KEY)
		player_move(game, player_tile, player_tile->down_tile);
	else
		return (0);
	return (1);
}
