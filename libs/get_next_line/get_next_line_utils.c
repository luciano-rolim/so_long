/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:50:15 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/05/10 12:24:42 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	custom_malloc(void **allocate, size_t size, t_node **linked_list)
{
	if (allocate == NULL)
		return (0);
	*allocate = malloc(size);
	if (*allocate == NULL)
	{
		free_all(linked_list);
		return (0);
	}
	return (1);
}

int	has_new_line(t_node *node_to_check, size_t *str_len)
{
	size_t	i;

	if (node_to_check == NULL)
		return (0);
	i = 0;
	while (node_to_check->str[i])
	{
		(*str_len)++;
		if (node_to_check->str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	node_to_str(t_node *linked_list, char *line)
{
	int	i;
	int	j;

	if (linked_list == NULL || line == NULL)
		return (0);
	j = 0;
	while (linked_list)
	{
		i = 0;
		while (linked_list->str[i])
		{
			if (linked_list->str[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return (1);
			}
			line[j++] = linked_list->str[i++];
		}
		linked_list = linked_list->next;
	}
	line[j] = '\0';
	return (1);
}

int	surplus_treatment(t_node **list, t_node **last_node)
{
	t_node	*tmp;
	int		i;
	int		j;
	char	*buf;

	if (!custom_malloc((void **)&buf, BUFFER_SIZE + 1, list))
		return (0);
	if (!custom_malloc((void **)&tmp, sizeof(t_node), list))
		return (0);
	i = 0;
	j = 0;
	while ((*last_node)->str[i] && (*last_node)->str[i] != '\n')
		i++;
	while ((*last_node)->str[i] && (*last_node)->str[++i])
		buf[j++] = (*last_node)->str[i];
	buf[j] = '\0';
	tmp->str = buf;
	tmp->next = NULL;
	if (!list_redefine(list, tmp, buf))
		return (0);
	return (1);
}

int	list_redefine(t_node **linked_list, t_node *clean_node, char *buf)
{
	if (*linked_list == NULL || clean_node == NULL || buf == NULL)
		return (0);
	if (!free_all(linked_list))
		return (0);
	if (clean_node->str[0] != '\0')
		*linked_list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
	return (1);
}
