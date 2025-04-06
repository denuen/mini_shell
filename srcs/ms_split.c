/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:47:31 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/06 23:14:43 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

int		ft_get_words(const char *s, char sep);
int		ft_get_letters(const char *s, char sep);
void	ft_check_for_quotes(char **line);
void	ft_check_for_redir(char **line);
char	**ms_split_fill(char **split, char *s, char sep, int words);

char	**ms_split(char *s, char sep)
{
	char	**split;
	int		words;

	if (!s)
		return (NULL);
	ft_check_for_quotes(&s);
	ft_check_for_redir(&s);
	words = ft_get_words(s, sep);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	return (ms_split_fill(split, s, sep, words));
}

char	**ms_split_fill(char **split, char *s, char sep, int words)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] && j < words)
	{
		while (s[i] && s[i] == sep)
			i++;
		len = ft_get_letters(&s[i], sep);
		if (len > 0)
		{
			split[j] = ft_substr(s, i, len);
			j++;
			i += len;
		}
	}
	split[j] = NULL;
	return (split);
}

int	ft_get_letters(const char *s, char sep)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (s[i] == sep && !in_squote && !in_dquote)
			break ;
		i++;
	}
	return (i);
}

int	ft_process_word(const char *s, char sep, int *i)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (s[*i])
	{
		if (s[*i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[*i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (s[*i] == sep && !in_squote && !in_dquote)
			return (0);
		(*i)++;
	}
	return (0);
}

int	ft_get_words(const char *s, char sep)
{
	int	i;
	int	words;
	int	in_squote;
	int	in_dquote;

	i = 0;
	words = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (s[i] == sep && !in_squote && !in_dquote)
		{
			i++;
			continue ;
		}
		else if (!in_squote && !in_dquote)
		{
			words++;
			ft_process_word(s, sep, &i);
			continue ;
		}
		i++;
	}
	return (words);
}










