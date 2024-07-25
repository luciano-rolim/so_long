/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:25:44 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 12:21:23 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	clean_images(t_game *game)
{
	if (!game)
		return ;
	destroy_image(game->mlx_ptr, game->images.player);
	destroy_image(game->mlx_ptr, game->images.background);
	destroy_image(game->mlx_ptr, game->images.wall);
	destroy_image(game->mlx_ptr, game->images.exit);
	destroy_image(game->mlx_ptr, game->images.exit_player);
	destroy_image(game->mlx_ptr, game->images.collectible);
}

static void	ft_full_grid_clean(t_game *game)
{
	int	x;
	int	y;

	if (!game)
		return ;
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		x = 0;
		while (x < game->map.horiz_tiles)
		{
			if (game->map.grid[y][x])
				free(game->map.grid[y][x]);
			x++;
		}
		if (game->map.grid[y])
			free(game->map.grid[y]);
		y++;
	}
	free(game->map.grid);
}

static void	clean_lines(t_game *game)
{
	t_line	*tmp;

	if (!game)
		return ;
	tmp = NULL;
	tmp = game->map.list;
	while (tmp)
	{
		free(tmp->content);
		game->map.list = tmp->next_line;
		free (tmp);
		tmp = game->map.list;
	}
}

int	exit_program(char *message, t_close_status status)
{
	if (status == CLOSE_SUCCESS)
	{
		if (message)
			ft_printf("%s\n", message);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (message)
		{
			if (status == CLOSE_FAIL)
				perror(message);
			else
				ft_printf("%s\n", message);
		}
		exit(EXIT_FAILURE);
	}
}

void	end_game(char *message, t_game *game, t_close_status status)
{
	if (game)
	{
		if (game->map.grid)
			ft_full_grid_clean(game);
		if (game->window)
			mlx_destroy_window(game->mlx_ptr, game->window);
		if (game->map.list)
			clean_lines(game);
		clean_images(game);
		if (game->mlx_ptr)
		{
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
		}
	}
	exit_program(message, status);
}
