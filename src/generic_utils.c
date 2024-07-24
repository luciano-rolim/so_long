/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:01:21 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 16:26:02 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_image(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->window, image, x * TILE_HEIGHT, y * TILE_WIDTH);
}

void	search_valid_path(t_game *game, t_tile *current_tile)
{
	if (!game)
		close_game("Error\nInvalid search_valid_path call", NULL, CLOSE_OTHERS);
	if (!current_tile)
		return ;
	if (current_tile->checked == 1)
		return ;
	current_tile->checked = 1;
	if (current_tile->type == WALL)
		return ;
	else if (current_tile->type == COLLECTIBLE)
		game->tmp_var.collectables_found++;
	else if (current_tile->type == EXIT)
		game->tmp_var.exit_found++;
	search_valid_path(game, current_tile->up_tile);
	search_valid_path(game, current_tile->right_tile);
	search_valid_path(game, current_tile->down_tile);
	search_valid_path(game, current_tile->left_tile);
}
