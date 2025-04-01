/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:24:29 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/01 15:57:10 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

#define SINGLE_QUOTE	0
#define DOUBLE_QUOTE	1
#define DOLLAR			2
#define WILDCARD		3

/*
' $ ' -> non espandibile
" $ " -> espandibile
*/

// Dichiarazione della funzione wildcard esterna
char	*ms_handlewildcard(char *string);

static char	*ms_replace_expline(char *env_value, char *line, int start, int end)
{
	char	*tmp_value;

	if (start > 0)
		tmp_value = ms_strnjoin(NULL, line, start - 1);
	else
		tmp_value = ft_strdup("");
	tmp_value = ms_strnjoin(tmp_value, env_value, ft_strlen(env_value));
	tmp_value = ms_strnjoin(tmp_value, &(line[end]), ft_strlen(&line[end]));
	return (tmp_value);
}

static char	*ft_expansion(t_minishell *ms, char *string, int start)
{
	t_env	*to_find;
	char	*join;
	t_env	tmp;
	int		end;

	end = start;
	while (string[end] && string[end] != ' ' && string[end] != '"')
		end++;
	tmp.name = ft_substr(string, start, end - start);
	to_find = ft_env_find(ms->envs, tmp.name);
	if (!to_find)
		to_find = ft_env_find(ms->vars, tmp.name);
	if (to_find)
		tmp.value = ms_replace_expline(to_find->value, string, start, end);
	else
		tmp.value = ft_strdup(string);
	free(tmp.name);
	free(string);
	return (tmp.value);
}

static char	*ft_tryexpansion(t_minishell *ms, char *string)
{
	char	*expanded;
	int		checks[4];

	checks[DOLLAR] = ft_findchr(string, '$');
	checks[WILDCARD] = ft_findchr(string, '*');
	if (checks[DOLLAR] < 0 && checks[WILDCARD] < 0)
		return (string);
	if (checks[DOLLAR] > 0)
	{
		checks[SINGLE_QUOTE] = ft_findchr(string, '\'');
		checks[DOUBLE_QUOTE] = ft_findchr(string, '"');
		if (checks[SINGLE_QUOTE] >= 0 && (checks[DOUBLE_QUOTE] < 0
				|| (checks[DOUBLE_QUOTE] > checks[SINGLE_QUOTE])))
			expanded = string;
		else
			expanded = ft_expansion(ms, string, checks[DOLLAR] + 1);
	}
	if (checks[WILDCARD] > 0)
		expanded = ms_handlewildcard(string);
	return (expanded);
}

char	**ft_rearrange_line(t_minishell *ms, char **split)
{
	char	**new_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (split[i] && ft_findchr(split[i], '=') > 0)
		i++;
	while (split[i + j])
	{
		split[i + j] = ft_tryexpansion(ms, split[i + j]);
		if (!split[i + j])
			return (NULL);
		j++;
	}
	new_split = (char **)malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (split[i + j])
	{
		new_split[j] = ft_strdup(split[i + j]);
		j++;
	}
	new_split[j] = NULL;
	ft_matrix_destroy(split);
	return (new_split);
}
