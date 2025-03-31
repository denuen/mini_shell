/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:40:43 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/25 11:50:18 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stddef.h>
#include <stdlib.h>

static int	ms_wait_for_eof(char *s, char *open, int *i);
char		**ms_ssalloc(const char *s, const char c);

void	ms_counter(char s, char *open, size_t *cnt, int *i)
{
	if (s == '\0')
		return ;
	if ((s == '"' || s == '\'') && *open == '\0')
	{
		*open = s;
		(*cnt)++;
	}
	else if (s == *open && *open != '\0')
	{
		*open = '\0';
		(*cnt)++;
	}
	else
		(*cnt)++;
}

char	**ms_misery_init(size_t *i, size_t *k, const char *s, char c)
{
	*i = 0;
	*k = 0;
	return (ms_ssalloc(s, c));
}

int	ms_split_checks(char *s, char *open, int *i)
{
	if (s[*i] == '\0')
		return (ms_wait_for_eof(s, open, i));
	else if (!ft_strncmp(&(s[*i]), "<<", 2))
		return (ms_wait_for_eof(s, NULL, i));
	else if ((s[*i] == '"' || s[*i] == '\'') && *open == '\0')
		*open = s[*i];
	else if (s[*i] == *open && *open != '\0')
		*open = '\0';
	(*i)++;
	return (0);
}

static char	*ms_set_waitingparams(char *s, int *i, char **kw, char **endl)
{
	char	*tmp;

	if (i == NULL)
	{
		*kw = "quote> ";
		*endl = ft_strdup(s);
	}
	else
	{
		*kw = "heredoc> ";
		tmp = ft_strchr(&(s[*i]), ' ');
		if (tmp == NULL)
			tmp = ft_strchr(&(s[*i]), '\0');
		*endl = ft_substr(s, *i + 2, tmp - &(s[*i]) - 2);
	}
	return (ft_strdup(""));
}

static int	ms_wait_for_eof(char *s, char *open, int *i)
{
	char	*line;
	char	*joined;
	char	*keyword;
	char	*endline;

	if ((!open && !i) || !s)
		return (0);
	joined = ms_set_waitingparams(s, i, &keyword, &endline);
	line = readline(keyword);
	while (line)
	{
		if (ft_strnstr(line, endline, ft_strlen(endline)))
		{
			joined = ms_strnjoin(joined, line, ft_strlen(line));
			break ;
		}
		joined = ms_strnjoin(joined, line, ft_strlen(line));
		free(line);
		line = readline(keyword);
	}
	free(line);
	free(endline);
	free(joined);
	return (1);
}
