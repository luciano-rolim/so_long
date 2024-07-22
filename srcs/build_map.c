/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:15:02 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 11:04:34 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	line_validation(t_game *game, char *buffer, int line_count, int line_len, int file_fd)
{
	if (!game || file_fd == -1)
		close_game("Error\nInvalid line_validation call", game, CLOSE_OTHERS);		
	if (line_count == 0)
	{
		if (!ft_is_string_char_set(buffer, "1"))
			handle_line_error("Error\nFirst row must be made only by walls", game, buffer, file_fd);
		else
			game->map.horizontal_tiles = (line_len);
	}
	else
	{
		if (buffer[0] != '1' || buffer[line_len - 1] != '1')
			handle_line_error("Error\nMap is not surrounded by walls", game, buffer, file_fd);
		if ((line_len) != game->map.horizontal_tiles)
			handle_line_error("Error\nMap is not rectangular", game, buffer, file_fd);
	}
	if (!ft_is_string_char_set(buffer, game->map.types))
		handle_line_error("Error\nInvalid map char", game, buffer, file_fd);
}

static void	line_reading(t_game *game)
{
	int line_len;

	if (!game)
		close_game("Error\nInvalid line_reading call", NULL, CLOSE_OTHERS);		
	line_len = 0;
	while (1)
	{
		game->tmp_var.buffer = get_next_line(game->tmp_var.file_fd);
		if (!game->tmp_var.buffer)
		{
			if (game->tmp_var.line_count == 0)
				handle_line_error("Error\nMap file is empty", game, game->tmp_var.buffer, game->tmp_var.file_fd);
			else
				break ;
		}
		line_len = ft_strlen(game->tmp_var.buffer);
		if (game->tmp_var.buffer[line_len - 1] == '\n')
		{
			game->tmp_var.buffer[line_len - 1] = '\0';
			line_len -= 1;
		}
		line_validation(game, game->tmp_var.buffer, game->tmp_var.line_count, line_len, game->tmp_var.file_fd);
		add_new_node(game, game->tmp_var.buffer);
		game->tmp_var.line_count++;
	}
}

void	build_map(t_game *game, char *filename)
{
	if (!game || !filename)
		close_game("Error\nInvalid build_map call", game, CLOSE_OTHERS);
	game->tmp_var.file_fd = open(filename, O_RDONLY);
	if (game->tmp_var.file_fd == -1)
		close_game("Error\nOpen function failure", game, CLOSE_FAILURE);
	line_reading(game);
	game->map.vertical_tiles = game->tmp_var.line_count;
	additional_map_checks(game, game->tmp_var.buffer, game->tmp_var.file_fd);
	clean_buffer_fd_gnl(game->tmp_var.buffer, game->tmp_var.file_fd, game);
}