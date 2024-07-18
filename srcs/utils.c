/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:58:24 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/18 12:43:12 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
{
	if (!game || !old_pos || !new_pos)
		close_game("Error on player_move call", game, CLOSE_FAILURE);

	old_pos->type = '0';
	new_pos->type = 'P';
	game->player.tile = new_pos;
	new_pos->image = game->images.player;
	old_pos->image = game->images.background;
	mlx_put_image_to_window(game->mlx_ptr, game->window, game->images.background, \
	((old_pos->x_grid) * TILE_WIDTH), ((old_pos->y_grid) * TILE_HEIGHT));
	mlx_put_image_to_window(game->mlx_ptr, game->window, game->images.player, \
	((new_pos->x_grid) * TILE_WIDTH), ((new_pos->y_grid) * TILE_HEIGHT));
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




	// printf("\n\n\nINFO BEFORE THE MOVEMENT\n");
	// print_info(game);

	// printf("\n\n\nINFO AFTER THE MOVEMENT\n");
	// print_info(game);


/*

// void	player_move(t_game *game, t_tile *old_pos, t_tile *new_pos)
// {
// 	// t_image	new_empty;
// 	// t_image	new_player;

// 	if (!game || !old_pos || !new_pos)
// 		close_game("Error on player_move call", game, CLOSE_FAILURE);

// 	// new_empty.image_ptr = NULL;
// 	// new_empty.address = NULL;
// 	// new_player.image_ptr = NULL;
// 	// new_player.address = NULL;

// 	old_pos->type = '0';
// 	new_pos->type = 'P';
// 	game->player.tile = new_pos;
// 	new_pos->image = game->images.player;
// 	old_pos->image = game->images.background;

// 	// new_empty.image_ptr = image_creation(game, old_pos);
// 	// new_player.image_ptr = image_creation(game, new_pos);
// 	// mlx_put_image_to_window(game->mlx_ptr, game->window, new_empty.image_ptr, \
// 	// ((old_pos->x_grid) * TILE_WIDTH), ((old_pos->y_grid) * TILE_HEIGHT));
// 	// mlx_put_image_to_window(game->mlx_ptr, game->window, new_player.image_ptr, \
// 	// ((new_pos->x_grid) * TILE_WIDTH), ((new_pos->y_grid) * TILE_HEIGHT));

// 	mlx_put_image_to_window(game->mlx_ptr, game->window, game->images.background, \
// 	((old_pos->x_grid) * TILE_WIDTH), ((old_pos->y_grid) * TILE_HEIGHT));

// 	mlx_put_image_to_window(game->mlx_ptr, game->window, game->images.player, \
// 	((new_pos->x_grid) * TILE_WIDTH), ((new_pos->y_grid) * TILE_HEIGHT));

// 	// mlx_destroy_image(game->mlx_ptr, old_pos->image);
// 	// mlx_destroy_image(game->mlx_ptr, new_pos->image);

// }


// void print_info(t_game *game)
// {
// 	printf("\n\n");
//     printf("Game mlx_ptr is %p\n", game->mlx_ptr);
//     printf("Game window is %p\n", game->window);
//     printf("Game tile_width is %d\n", game->tile_width);
//     printf("Game tile_height is %d\n", game->tile_height);
//     printf("Game pixel_width is %d\n", game->pixel_width);
//     printf("Game pixel_height is %d\n", game->pixel_height);
//     printf("Game grid pointer is %p\n", game->grid);

//     // Print Player attributes
// 	printf("\n\n");
//     printf("Player tile pointer is %p\n", game->player.tile);

// 	printf("\n\n");
//     printf("Tile (0,0) pointer is %p\n", game->grid[0][0]);
//     printf("Tile (0,0) image pointer is %p\n", game->grid[0][0]->image);
// 	printf("Tile (0,0) x_grid is %d\n", game->grid[0][0]->x_grid);
//     printf("Tile (0,0) y_grid is %d\n", game->grid[0][0]->y_grid);
//     printf("Tile (0,0) type is %c\n", game->grid[0][0]->type);
//     printf("Tile (0,0) right_tile pointer is %p\n", game->grid[0][0]->right_tile);
//     printf("Tile (0,0) left_tile pointer is %p\n", game->grid[0][0]->left_tile);
//     printf("Tile (0,0) up_tile pointer is %p\n", game->grid[0][0]->up_tile);
//     printf("Tile (0,0) down_tile pointer is %p\n", game->grid[0][0]->down_tile);

//     // Print Tile at position (0,1)
// 	printf("\n\n");
//     printf("Tile (0,1) pointer is %p\n", game->grid[0][1]);
//     printf("Tile (0,1) image pointer is %p\n", game->grid[0][1]->image);
//     printf("Tile (0,1) x_grid is %d\n", game->grid[0][1]->x_grid);
//     printf("Tile (0,1) y_grid is %d\n", game->grid[0][1]->y_grid);
//     printf("Tile (0,1) type is %c\n", game->grid[0][1]->type);
//     printf("Tile (0,1) right_tile pointer is %p\n", game->grid[0][1]->right_tile);
//     printf("Tile (0,1) left_tile pointer is %p\n", game->grid[0][1]->left_tile);
//     printf("Tile (0,1) up_tile pointer is %p\n", game->grid[0][1]->up_tile);
//     printf("Tile (0,1) down_tile pointer is %p\n", game->grid[0][1]->down_tile);
// }

*/