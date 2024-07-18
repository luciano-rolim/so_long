/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:25:44 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/18 12:46:28 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void clean_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->images.player);
	mlx_destroy_image(game->mlx_ptr, game->images.background);
	mlx_destroy_image(game->mlx_ptr, game->images.wall);
}

void	ft_full_grid_clean(t_game *game)
{
	if(!game)
		return ;
	int	x;
	int	y;

	y = 0;
	while (y < game->tile_height)
	{
		x = 0;
		while (x < game->tile_width)
		{
			if (game->grid[y][x])
				free(game->grid[y][x]);
			x++;
		}
		if (game->grid[y])
			free(game->grid[y]);
		y++;
	}
	free(game->grid);
}

int	close_game(char *message, t_game *game, t_close_status status)
{
	clean_images(game);
	ft_full_grid_clean(game);
	if (game->window)
	{
		mlx_clear_window(game->mlx_ptr, game->window);
		mlx_destroy_window(game->mlx_ptr, game->window);
	}
	if (game)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (status == CLOSE_SUCCESS)
		exit(EXIT_SUCCESS);
	else
	{
		if (message)
			perror(message);
		exit(EXIT_FAILURE);
	}
}
