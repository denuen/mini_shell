/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:01:21 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 09:24:03 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

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

static int	ms_match_segments(char **segments, char *filename)
{
	int	i;
	int	last_pos;
	int	found;

	i = 0;
	last_pos = 0;
	while (segments[i])
	{
		if (i == 0 && ft_strlen(segments[i]) > 0)
			i++;
		else
		{
			found = ms_find_segment(segments[i], filename, &last_pos);
			if (!found)
				return (0);
			i++;
		}
	}
	return (1);
}

int	ms_wdcard_match(char *string, char *filename)
{
	int		s_len;
	int		f_len;
	char	**segments;
	int		result;

	if (!string || !filename)
		return (0);
	s_len = ft_strlen(string);
	f_len = ft_strlen(filename);
	if (s_len == 1 && string[0] == '*')
		return (1);
	if (!ms_check_prefix(string, filename))
		return (0);
	if (!ms_check_suffix(string, filename, s_len, f_len))
		return (0);
	segments = ft_split(string, '*');
	if (!segments)
		return (0);
	result = ms_match_segments(segments, filename);
	ft_matrix_destroy((void **)segments);
	return (result);
}
