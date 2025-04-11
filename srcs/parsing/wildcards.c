/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:00:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 00:31:53 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>
#include <stdlib.h>

void		ft_upd_qstate(char c, int *in_squote, int *in_dquote);
int			ms_check_prefix(char *string, char *filename);
int			ms_check_suffix(char *string, char *filename, int s_len, int f_len);
int			ms_find_segment(char *segment, char *filename, int *last_pos);
int			ms_wdcard_match(char *string, char *filename);

static void	ms_append_match(char **wdcard, char *filename)
{
	if (!filename || !wdcard)
		return ;
	if (*wdcard == NULL)
	{
		*wdcard = ft_strdup(filename);
		return ;
	}
	*wdcard = ms_strnjoin(*wdcard, " ", 1);
	*wdcard = ms_strnjoin(*wdcard, filename, ft_strlen(filename));
}

static char	*ms_process_wildcard(char *string)
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
		if (entry->d_name[0] != '.' || (string[0] == '.' && string[1] == '*'))
		{
			if (ft_strlen(string) == 1 && string[0] == '*')
				ms_append_match(&wdcard, entry->d_name);
			else if (ms_wdcard_match(string, entry->d_name))
				ms_append_match(&wdcard, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (!wdcard)
		return (string);
	free(string);
	return (wdcard);
}

char	*ms_expand_wildcard(char *str, int *changed)
{
	char	**words;
	char	*result;
	char	*temp;
	int		i;
	int		word_changed;

	words = ft_split(str, ' ');
	result = ft_strdup("");
	i = -1;
	while (words[++i])
	{
		if (ft_strchr(words[i], '*'))
		{
			word_changed = 0;
			temp = ms_process_wildcard(words[i]);
			words[i] = temp;
			if (word_changed)
				*changed = 1;
		}
		if (i > 0)
			result = ms_strnjoin(result, " ", 1);
		result = ms_strnjoin(result, words[i], ft_strlen(words[i]));
	}
	ft_matrix_destroy((void **)words);
	return (result);
}

void	ft_check_for_wildcard(char **line)
{
	char	*result;
	int		changed;
	int		max_iter;
	int		iter_count;

	result = *line;
	max_iter = 5;
	iter_count = 0;
	changed = 1;
	while (changed && iter_count < max_iter)
	{
		changed = 0;
		result = ms_expand_wildcard(result, &changed);
		iter_count++;
	}
	*line = result;
}
