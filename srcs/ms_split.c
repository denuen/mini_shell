/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:47:50 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/03 15:21:41 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char			**ms_misery_init(size_t *i, size_t *k, const char *s, char c);
static char		**ms_salloc(char **ss, const char *s, size_t *k, size_t cnt);
void			ms_counter(char s, char *open, size_t *cnt, int *i);
static size_t	ms_wordcounter(const char *s, const char c);
int				ms_split_checks(char *s, char *open, int *i);
char			**ms_ssalloc(const char *s, const char c);
static void		*ms_ssdestroy(char **ss);
int				ms_wait_for_eof(char *s, char *open, int *i);

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
		if (s[i] == c && open == '\0')
			i++;
		else
		{
			while ((s[i + cnt] != '\0' && (s[i + cnt] != c || open != '\0')))
				ms_counter(s[i + cnt], &open, &cnt, (int *)&i);
			if (cnt > 0 && ms_salloc(ss, &(s[i]), &k, cnt) == NULL)
				return (ms_ssdestroy(ss));
			i += cnt;
		}
	}
	if (open != '\0')
		ms_wait_for_eof((char *)s, &open, NULL);
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
		if (s[i] == c && open == '\0')
			i++;
		else
		{
			words++;
			while (s[i] != '\0' && (s[i] != c || open != '\0'))
				ms_split_checks((char *)s, &open, (int *)&i);
		}
	}
	return (words);
}

char	**ms_ssalloc(const char *s, const char c)
{
	char	**ss;
	size_t	n;

	if (!s)
		return (NULL);
	n = ms_wordcounter(s, c);
	ss = (char **)malloc(sizeof(char *) * (n + 1));
	if (ss == NULL)
		return (NULL);
	ss[n] = NULL;
	return (ss);
}

static char	**ms_salloc(char **ss, const char *s, size_t *k, size_t cnt)
{
	size_t	i;
	char	open;

	open = '\0';
	i = 0;
	if (s == NULL || cnt == 0)
		return (NULL);
	ss[*k] = (char *)malloc(sizeof(char) * (cnt + 1));
	if (ss[*k] == NULL)
		return (NULL);
	while (i < cnt)
	{
		if ((s[i] == '"' || s[i] == '\'') && open == '\0')
			open = s[i];
		else if (s[i] == open && open != '\0')
			open = '\0';
		ss[*k][i] = s[i];
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
