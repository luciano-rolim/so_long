/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:01:21 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 11:01:32 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destroy_image(void *mlx_ptr, void *image)
{
	if (!mlx_ptr || !image)
		return ;
	mlx_destroy_image(mlx_ptr, image);
}

void	put_image(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->window, \
	image, x * TILE_HEIGHT, y * TILE_WIDTH);
}

void	search_valid_path(t_game *game, t_tile *current_tile)
{
	if (!game)
		end_game("Error\nInvalid search_valid_path call", NULL, CLOSE_OTHER);
	if (!current_tile)
		return ;
	if (current_tile->checked == 1)
		return ;
	current_tile->checked = 1;
	if (current_tile->type == WALL)
		return ;
	else if (current_tile->type == COLLECTIBLE)
		game->var.collects_found++;
	else if (current_tile->type == EXIT)
		game->var.exit_found++;
	search_valid_path(game, current_tile->up_tile);
	search_valid_path(game, current_tile->right_tile);
	search_valid_path(game, current_tile->down_tile);
	search_valid_path(game, current_tile->left_tile);
}
