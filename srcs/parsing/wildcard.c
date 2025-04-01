/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:13:34 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/01 17:10:45 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>
#include <stdlib.h>

// Dichiarazioni esterne delle funzioni in wildcard_utils.c
int		ms_check_prefix(char *string, char *filename);
int		ms_find_segment(char *segment, char *filename, int *last_pos);
int		ms_check_suffix(char *string, char *filename, int s_len, int f_len);

static int	ms_match_segments(char **segments, char *filename)
{
	int	i;
	int	last_pos;
	int	segment_len;
	int	found;

	i = 0;
	last_pos = 0;
	while (segments[i])
	{
		if (i == 0 && ft_strlen(segments[i]) > 0)
			i++;
		else
		{
			segment_len = ft_strlen(segments[i]);
			found = ms_find_segment(segments[i], filename, &last_pos);
			if (!found)
				return (0);
			i++;
		}
	}
	return (1);
}

static int	ms_wdcard_match(char *string, char *filename)
{
	int		s_len;
	int		f_len;
	char	**segments;
	int		result;

	if (!string || !filename)
		return (0);
	s_len = ft_strlen(string);
	f_len = ft_strlen(filename);
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

static void	ms_append_match(char **wdcard, char *filename)
{
	*wdcard = ms_strnjoin(*wdcard, " ", 1);
	*wdcard = ms_strnjoin(*wdcard, filename, ft_strlen(filename));
}

char	*ms_handlewildcard(char *string)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*wdcard;

	wdcard = NULL;
	dir = opendir(".");
	if (!dir)
		return (string);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && ms_wdcard_match(string, entry->d_name))
			ms_append_match(&wdcard, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	if (!wdcard)
		return (string);
	free(string);
	return (wdcard);
}
