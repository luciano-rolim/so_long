/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_string_char_set.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:47:23 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 13:47:28 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_string_char_set(char *full_str, char *char_set)
{
	int	i;
	int	j;
	int	is_valid;

	i = 0;
	if (!full_str || !char_set)
		return (0);
	while (full_str[i])
	{
		j = 0;
		is_valid = 0;
		while (char_set[j])
		{
			if (full_str[i] == char_set[j])
			{
				is_valid = 1;
				break ;
			}
			j++;
		}
		if (!is_valid)
			return (0);
		i++;
	}
	return (1);
}
