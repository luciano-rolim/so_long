/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:23:28 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 15:25:35 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clean_buffer_fd_gnl(char* buffer, int file_fd, t_game *game)
{
	if (!game || file_fd == -1)
		close_game("Error\nInvalid clean_buffer_fd_gnl call", game, CLOSE_OTHERS);
	if (buffer)
		free(buffer);
	while ((buffer = get_next_line(file_fd)) != NULL)
		free(buffer);
	close(file_fd);
}

void	handle_line_error(char *message, t_game *game, char *buffer, int file_fd)
{
	if (!game)
		close_game("Error\nInvalid handle_line_error call", game, CLOSE_OTHERS);
	clean_buffer_fd_gnl(buffer, file_fd, game);
	close_game(message, game, CLOSE_OTHERS);
}

static int item_count(t_game *game, char to_count)
{
	int		i;
	int 	item_count;
	t_line	*tmp;

	if (!game)
		close_game("Error\nInvalid item count function call", game, CLOSE_OTHERS);
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

void	additional_map_checks(t_game *game, char *buffer, int file_fd)
{
	t_line	*last_row;

	if (!game || file_fd == -1)
		close_game("Error\nInvalid additional_map_checks call", game, CLOSE_OTHERS);
	last_row = last_node(game, game->map.list);
	if (!ft_is_string_char_set(last_row->content, "1"))
		handle_line_error("Error\nLast row must be made only by walls", game, buffer, file_fd);
	if (item_count(game, 'P') != 1)
		handle_line_error("Error\nGame must have exactly one player", game, buffer, file_fd);
	if (item_count(game, 'E') != 1)
		handle_line_error("Error\nGame must have exactly one exit", game, buffer, file_fd);
	game->map.collectibles = item_count(game, 'C');
	if (game->map.collectibles < 1)
		handle_line_error("Error\nGame must have at least one collectible", game, buffer, file_fd);
}
