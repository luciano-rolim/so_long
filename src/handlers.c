/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:45:29 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/23 23:18:56 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int mouse_close_handler(t_game *game)
{
    close_game("Game closed after 'x' was clicked", game, CLOSE_SUCCESS);
    return (0);
}
int	key_press_handler(int key, t_game *game)
{
	t_tile	*player_tile;

	if (!game)
		close_game("Error\nError on key_press call", NULL, CLOSE_OTHERS);
	player_tile = game->player.tile;
	if (key == ESC)
		close_game("Game closed after ESC key was pressed", game, CLOSE_SUCCESS);
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
