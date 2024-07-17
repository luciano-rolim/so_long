/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:25:44 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/17 15:55:28 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
			{
				if (game->grid[y][x]->image)
					mlx_destroy_image(game->mlx_ptr, game->grid[y][x]->image); //Error line
				free(game->grid[y][x]);
			}
			x++;
		}
		if (game->grid[y])
			free(game->grid[y]);
		y++;
	}
	free(game->grid);
}

int	close_game(char *message, t_game *game, close_status status)
{
	ft_full_grid_clean(game);
	if (game->window)
	{
		mlx_clear_window(game->mlx_ptr, game->window);
		mlx_destroy_window(game->mlx_ptr, game->window);
	}
	if (game)
		mlx_destroy_display(game->mlx_ptr);
	if (status == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else
	{
		if (message)
			perror(message);
		exit(EXIT_FAILURE);
	}
}
