/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/16 09:43:54 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int close_game_failure(t_game *game, t_image* image)
{
	if (image)
		mlx_destroy_image(game->mlx_connection, image->image);
	if (game->window)
		mlx_destroy_window(game->mlx_connection, game->window);
	mlx_destroy_display(game->mlx_connection);
	exit(EXIT_FAILURE);
}

int close_game_success(t_game *game)
{
	// if (image->image)
	// 	mlx_destroy_image(game->mlx_connection, )
	if (game->window)
		mlx_destroy_window(game->mlx_connection, game->window);
	mlx_destroy_display(game->mlx_connection);
	exit(EXIT_SUCCESS);
}

int player_movement(t_tile* old_position, t_tile* new_position)
{

	image_creation();
	mlx_put_image_to_window();

	image_creation();
	mlx_destroy_image(old_position.image);

	mlx_put_image_to_window(old_position.image);

	player.tile = draw_tile();
	player.tile_right = player.tile;
}

int	key_press(int key, t_game* game)
{
	if (key == ESC)
		close_game_success(game);
	else if (key == RIGHT_KEY)
		player_movement(t_player.tile, player.right_tile);
	else if (key == LEFT_KEY)
		player_movement(t_player.tile, player.tile.left_tile);
	else if (key == UP_KEY)
		player_movement(t_player.tile, player.tile.up_tile);
	else if (key == DOWN_KEY)
		player_movement(t_player.tile, player.tile.down_tile);
	else
		return (0);
	return (1);
}