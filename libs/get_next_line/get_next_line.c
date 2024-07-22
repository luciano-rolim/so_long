/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:50:06 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/05/10 18:39:04 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	free_all(t_node **linked_list)
{
	t_node	*tmp;

	if (linked_list == NULL)
		return (0);
	while (*linked_list)
	{
		tmp = (*linked_list)->next;
		free((*linked_list)->str);
		free(*linked_list);
		*linked_list = tmp;
	}
	*linked_list = NULL;
	return (1);
}

char	*get_line(t_node *linked_list, size_t *str_len)
{
	char	*line;

	line = NULL;
	if (linked_list == NULL)
		return (NULL);
	if (!custom_malloc((void **)&line, (*str_len + 1), &linked_list))
		return (NULL);
	if (!node_to_str(linked_list, line))
		return (NULL);
	return (line);
}

int	node_concat(t_node **first_node, char *buf, t_node **last_node)
{
	t_node	*new_node;

	new_node = NULL;
	if (!custom_malloc((void **)&new_node, sizeof(t_node), first_node))
		return (0);
	new_node->str = buf;
	new_node->next = NULL;
	if (*first_node == NULL)
	{
		*first_node = new_node;
		*last_node = new_node;
	}
	else
	{
		(*last_node)->next = new_node;
		*last_node = new_node;
	}
	return (1);
}

int	node_creation(t_node **list, int fd, t_node **last_node, size_t *s_len)
{
	char	*buf;
	ssize_t	char_read;

	buf = NULL;
	while (!has_new_line(*last_node, s_len))
	{
		if (!custom_malloc((void **)&buf, BUFFER_SIZE + 1, list))
			return (0);
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			free_all(list);
			free(buf);
			return (0);
		}
		if (char_read == 0)
		{
			free(buf);
			return (0);
		}
		buf[char_read] = '\0';
		if (!node_concat(list, buf, last_node))
			return (0);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_node	*linked_list = NULL;
	t_node			*last_node;
	char			*line;
	size_t			str_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_all(&linked_list);
		return (NULL);
	}
	if (linked_list != NULL)
		last_node = linked_list;
	else
		last_node = NULL;
	str_len = 0;
	node_creation(&linked_list, fd, &last_node, &str_len);
	if (linked_list == NULL)
		return (NULL);
	line = get_line(linked_list, &str_len);
	if (!line)
		return (NULL);
	if (!surplus_treatment(&linked_list, &last_node))
		return (NULL);
	return (line);
}
