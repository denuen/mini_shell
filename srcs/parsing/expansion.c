/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 08:30:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 10:32:26 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

void	ft_update_quote_state(char c, int *in_squote, int *in_dquote);

static char	*ms_replace_variable(t_minishell *ms, \
						char *line, int start, int end)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	t_env	*env_var;

	var_name = ft_substr(line, start, end - start);
	env_var = ft_env_find(ms->envs, var_name);
	if (!env_var)
		env_var = ft_env_find(ms->vars, var_name);
	if (env_var)
		var_value = ft_strdup(env_var->value);
	else
		var_value = ft_strdup("");
	result = ft_substr(line, 0, start - 1);
	result = ms_strnjoin(result, var_value, ft_strlen(var_value));
	result = ms_strnjoin(result, &(line[end]), ft_strlen(&line[end]));
	free(var_name);
	free(var_value);
	free(line);
	return (result);
}

int	ft_isnot_delimiter(char c)
{
	return ((c != ' ' && c != '"'
			&& c != '\'' && c != '$' && c != '/'));
}

void	ft_get_startpos(int *start, int *i, char *str)
{
	*start = *i + 1;
	(*i)++;
	while (str[*i] && ft_isnot_delimiter(str[*i]))
		(*i)++;
}

char	*ms_expand_variable(t_minishell *ms, char *str, int *changed)
{
	int		i;
	int		in_quotes[2];
	int		start;
	char	*result;

	i = 0;
	in_quotes[0] = 0;
	in_quotes[1] = 0;
	while (str[i])
	{
		ft_update_quote_state(str[i], &in_quotes[0], &in_quotes[1]);
		if (str[i] == '$' && !in_quotes[0] && str[i + 1] \
			&& ft_isnot_delimiter(str[i + 1]))
		{
			ft_get_startpos(&start, &i, str);
			if (i > start)
			{
				*changed = 1;
				result = ms_replace_variable(ms, str, start, i);
				return (result);
			}
		}
		i++;
	}
	return (str);
}

void	ft_check_for_expansion(t_minishell *ms, char **line)
{
	char	*result;
	int		changed;
	int		max_iter;
	int		iter_count;

	result = *line;
	max_iter = 10;
	iter_count = 0;
	changed = 1;
	while (changed && iter_count < max_iter)
	{
		changed = 0;
		result = ms_expand_variable(ms, result, &changed);
		iter_count++;
	}
	*line = result;
}
