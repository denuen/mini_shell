/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:47:50 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/19 16:59:45 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ms_wordcounter(const char *s, const char c);
static char		**ms_ssalloc(const char *s, const char c);
static char		**ms_salloc(char **ss, const char *s, size_t *k, size_t cnt);
static void		*ms_ssdestroy(char **ss);

char	**ms_split(const char *s, char c)
{
	char	**ss;
	size_t	i;
	size_t	k;
	size_t	cnt;
	char	open;

	open = '\0';
	ss = ms_misery_init(&i, &k, s, c);
	if (ss == NULL || *s == '\0')
		return (ss);
	while (s[i] != '\0')
	{
		cnt = 0;
		if (s[i] == c)
			i++;
		else
		{
			while ((s[i + cnt] != '\0' && s[i + cnt] != c) || open != '\0')
				ms_counter(s[i + cnt], &open, &cnt);
			if (ms_salloc(ss, &(s[i]), &k, cnt) == NULL)
				return (ms_ssdestroy(ss));
		}
		i += cnt;
	}
	return (ss);
}


static size_t	ms_wordcounter(const char *s, const char c)
{
	size_t	i;
	size_t	words;
	char	open;

	i = 0;
	words = 0;
	open = '\0';
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while ((s[i] != '\0' && s[i] != c) || open != '\0')
				ms_split_checks(s[i], &open, &i);
		}
	}
	return (words);
}

static char	**ms_ssalloc(const char *s, const char c)
{
	char	**ss;
	size_t	n;

	if (!s)
		return (NULL);
	n = ms_wordcounter(s, c);
	ss = (char **) malloc(sizeof(char *) * (n + 1));
	if (ss == NULL)
		return (NULL);
	ss[n] = NULL;
	return (ss);
}

static char	**ms_salloc(char **ss, const char *s, size_t *k, size_t cnt)
{
	size_t	i;
	char	open;
	int	j;

	j = 0;
	open = '\0';
	i = 0;
	if (s == NULL || cnt == 0)
		return (NULL);
	ss[*k] = (char *) malloc(sizeof(char) * (cnt + 1));
	if (ss[*k] == NULL)
		return (NULL);
	while (i < cnt)
	{
		if ((s[i] == '"' || s == '\'') && open == '\0')
			open = s[i];
		else if (s[i] == open && open != '\0')
			open = '\0';
		if (!(s[i] == open && open != '\0'))
			j++;
		ss[*k][i] = s[i + j];
		i++;
	}
	ss[*k][i] = '\0';
	*k += 1;
	return (ss);
}

static void	*ms_ssdestroy(char **ss)
{
	int	i;

	if (!ss)
		return (NULL);
	i = 0;
	while (ss[i] != NULL)
	{
		free(ss[i]);
		i++;
	}
	free(ss);
	return (NULL);
}
