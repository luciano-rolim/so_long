/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:27:55 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 11:05:25 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_line	*last_node(t_game *game, t_line *head_node)
{
	t_line	*tmp_tile;

	if (!head_node)
		end_game("Error\nInvalid last_node call", game, CLOSE_OTHER);
	tmp_tile = head_node;
	while (tmp_tile->next_line)
		tmp_tile = tmp_tile->next_line;
	return (tmp_tile);
}

void	add_new_node(t_game *game, char *content)
{
	t_line	*new_node;
	t_line	*last_tile;

	if (!game || !content)
		end_game("Error\nError on add_new_node call", game, CLOSE_OTHER);
	new_node = malloc(sizeof(t_line));
	if (!new_node)
		end_game("Error\nmalloc failure on new node", game, CLOSE_FAIL);
	new_node->content = content;
	new_node->next_line = NULL;
	if (!game->map.list)
	{
		game->map.list = new_node;
		return ;
	}
	last_tile = last_node(game, game->map.list);
	last_tile->next_line = new_node;
}
