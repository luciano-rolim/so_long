/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:15:02 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 13:14:17 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	line_check(t_game *game, int line_count, int line_len, int fd)
{
	char	*buffer;

	if (!game || fd == -1 || !game->var.buffer)
		end_game("Error\nInvalid line_check call", game, CLOSE_OTHER);
	buffer = game->var.buffer;
	if (line_count == 0)
	{
		if (!ft_is_string_char_set(buffer, "1"))
			line_err("Error\nFirst row must be only walls", game, buffer, fd);
		else
			game->map.horiz_tiles = (line_len);
	}
	// if (!ft_is_string_char_set(last_row->content, "1"))
	// 	line_err("Error\nLast row must be made only by walls", game, buffer, fd);
	else
	{
		if (buffer[0] != '1' || buffer[line_len - 1] != '1')
			line_err("Error\nBorder is not wall", game, buffer, fd);
		if ((line_len) != game->map.horiz_tiles)
			line_err("Error\nMap is not rectangular", game, buffer, fd);
	}
	if (!ft_is_string_char_set(buffer, game->map.types))
		line_err("Error\nInvalid map char", game, buffer, fd);
}

static void	line_reading(t_game *game)
{
	int	line_len;

	if (!game)
		end_game("Error\nInvalid line_reading call", NULL, CLOSE_OTHER);
	line_len = 0;
	while (1)
	{
		game->var.buffer = get_next_line(game->var.fd);
		if (!game->var.buffer)
		{
			if (game->var.line_count == 0)
				line_err("Error\nNo map", game, game->var.buffer, game->var.fd);
			else
				break ;
		}
		line_len = ft_strlen(game->var.buffer);
		if (game->var.buffer[line_len - 1] == '\n')
		{
			game->var.buffer[line_len - 1] = '\0';
			line_len -= 1;
		}
		line_check(game, game->var.line_count, line_len, game->var.fd);
		add_new_node(game, game->var.buffer);
		game->var.line_count++;
	}
}

void	build_map(t_game *game, char *filename)
{
	if (!game || !filename)
		end_game("Error\nInvalid build_map call", game, CLOSE_OTHER);
	game->var.filename = filename;
	game->var.fd = open(game->var.filename, O_RDONLY);
	if (game->var.fd == -1)
		end_game("Error\nOpen function failure", game, CLOSE_FAIL);
	line_reading(game);
	game->map.vertical_tiles = game->var.line_count;
	additional_map_checks(game, game->var.buffer, game->var.fd);
	clean_buffer_fd_gnl(game->var.buffer, game->var.fd, game);
}
