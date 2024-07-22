/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 14:35:29 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void make_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	game->player.tile = new_pos;
	put_image(game, old_pos->image, old_pos->x_grid, old_pos->y_grid);
	put_image(game, new_pos->image, new_pos->x_grid, new_pos->y_grid);
	game->player.movements++;
	ft_printf("Current number of movements is %i\n", game->player.movements);		
}

void	entering_exit(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	old_pos->type = EMPTY;
	new_pos->type = EXIT_AND_PLAYER;
	old_pos->image = game->images.background;
	new_pos->image = game->images.exit_and_player;
	make_move(game, old_pos, new_pos);
}

void	leaving_exit(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	old_pos->type = EXIT;
	new_pos->type = PLAYER;
	old_pos->image = game->images.exit;
	new_pos->image = game->images.player;
	make_move(game, old_pos, new_pos);
}

void	standard_movement(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	old_pos->type = EMPTY;
	new_pos->type = PLAYER;
	new_pos->image = game->images.player;
	old_pos->image = game->images.background;
	make_move(game, old_pos, new_pos);
}

static void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		close_game("Error\nError on player_move call", game, CLOSE_FAILURE);
    if (game->player.movements == INT_MAX)
		close_game("Error\nMaximum number of movements reached\n", game, CLOSE_OTHERS);
	if (new_pos->type == PLAYER || new_pos->type == EXIT_AND_PLAYER)
		close_game("Error\nDuplicate player tile\n", game, CLOSE_OTHERS);
	if (new_pos->type == COLLECTIBLE)
		game->map.collectibles--;
	if (new_pos->type == WALL)
		return ;
	else if (new_pos->type == EXIT)
	{
		if (game->map.collectibles == 0)
		{
			standard_movement(game, old_pos, new_pos);
			ft_printf("You won!\n");
			close_game(NULL, game, CLOSE_SUCCESS);
		}
		else
			entering_exit(game, old_pos, new_pos);
	}
	else if (old_pos->type == EXIT_AND_PLAYER)
		leaving_exit(game, old_pos, new_pos);
	else if (new_pos->type == EMPTY || new_pos->type == COLLECTIBLE)
		standard_movement(game, old_pos, new_pos);
	else
		close_game("Error\nInvalid tile type\n", game, CLOSE_OTHERS);
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
