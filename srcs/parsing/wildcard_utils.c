/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:41:26 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/04 09:12:31 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_check_suffix(char *string, char *filename, int s_len, int f_len)
{
	int	i;
	int	j;

	if (s_len <= 0 || s_len > f_len)
		return (0);
	i = ft_strlen(string) - 1;
	j = ft_strlen(filename) - 1;
	while (i >= 0 && string[i] != '*')
	{
		if (string[i] != filename[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int	ms_check_prefix(char *string, char *filename)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '*')
	{
		if (string[i] != filename[i])
			return (0);
		i++;
	}
	return (1);
}

int	ms_find_segment(char *segment, char *filename, int *last_pos)
{
	int	i;
	int	j;
	int	segment_len;

	segment_len = ft_strlen(segment);
	if (segment_len == 0)
		return (1);
	i = *last_pos;
	while (filename[i])
	{
		j = 0;
		while (j < segment_len && filename[i + j] == segment[j])
			j++;
		if (j == segment_len)
		{
			*last_pos = i + segment_len;
			return (1);
		}
		i++;
	}
	return (0);
}
