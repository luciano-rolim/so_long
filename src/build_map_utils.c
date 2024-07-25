/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:23:28 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 13:33:21 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clean_buffer_fd_gnl(char *buffer, int file_fd, t_game *game)
{
	if (!game || file_fd == -1)
		end_game("Error\nInvalid clean_buffer_fd_gnl call", game, CLOSE_OTHER);
	if (buffer)
		free(buffer);
	close(file_fd);
	get_next_line(-1);
}

void	line_err(char *message, t_game *game, char *buffer, int fd)
{
	if (!game)
		end_game("Error\nInvalid line_err call", NULL, CLOSE_OTHER);
	clean_buffer_fd_gnl(buffer, fd, game);
	end_game(message, game, CLOSE_OTHER);
}

static int	item_count(t_game *game, char to_count)
{
	int		i;
	int		item_count;
	t_line	*tmp;

	if (!game)
		end_game("Error\nInvalid item count function call", game, CLOSE_OTHER);
	item_count = 0;
	tmp = game->map.list;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == to_count)
				item_count++;
			i++;
		}
		tmp = tmp->next_line;
	}
	return (item_count);
}

void	extra_map_checks(t_game *game, char *buff, int fd)
{
	t_line	*last_row;

	if (!game || fd == -1)
		end_game("Error\nInvalid extra_map_checks call", game, CLOSE_OTHER);
	last_row = last_node(game, game->map.list);
	if (!ft_is_string_char_set(last_row->content, "1"))
		line_err("Error\nLast row must be made only by walls", game, buff, fd);
	if (item_count(game, 'P') != 1)
		line_err("Error\nGame must have exactly one player", game, buff, fd);
	if (item_count(game, 'E') != 1)
		line_err("Error\nGame must have exactly one exit", game, buff, fd);
	game->map.collectibles = item_count(game, 'C');
	if (game->map.collectibles < 1)
		line_err("Error\nMap dont have a collectible", game, buff, fd);
}
