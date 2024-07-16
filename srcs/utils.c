/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/16 12:57:54 by lmeneghe         ###   ########.fr       */
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

void	player_movement(t_tile* old_position, t_tile* new_position, t_game* game)
{
	t_image	new_empty;
	t_image	new_player;

	old_position->type = '0';
	new_position->type = 'P';
	write(1, "test\n", 5);
	printf("and here mlx pointer is %p\n", game->mlx_connection);
	new_empty.image = image_creation(game, old_position);
	new_player.image = image_creation(game, new_position);
	mlx_put_image_to_window(game->mlx_connection, game->window, new_empty.image, ((old_position->x_grid) * TILE_WIDTH), \
	((old_position->y_grid) * TILE_HEIGHT));
	mlx_put_image_to_window(game->mlx_connection, game->window, new_player.image, ((new_position->x_grid) * TILE_WIDTH), \
	((new_position->y_grid) * TILE_HEIGHT));
	mlx_destroy_image(game->mlx_connection, old_position->image);
	mlx_destroy_image(game->mlx_connection, new_position->image);
	old_position->image = new_empty.image;
	new_position->image = new_empty.image;
	game->player.tile = new_position;
	tile_coordinates(game); //optmize to only adjust the required tiles
}

int	key_press(int key, t_game* game)
{
	t_tile*	player_tile;

	player_tile = game->player.tile;
	// printf("%p\n", player_tile->right_tile);
	printf("mlx pointer is %p\n", game->mlx_connection);
	if (key == ESC)
		close_game_success(game);
	else if (key == RIGHT_KEY)
	{
		write(1, "analyzis\n", 10);
		player_movement(player_tile, player_tile->right_tile, game);
	}
	else if (key == LEFT_KEY)
		player_movement(player_tile, player_tile->left_tile, game);
	else if (key == UP_KEY)
		player_movement(player_tile, player_tile->up_tile, game);
	else if (key == DOWN_KEY)
		player_movement(player_tile, player_tile->down_tile, game);
	else
		return (0);
	return (1);
}
