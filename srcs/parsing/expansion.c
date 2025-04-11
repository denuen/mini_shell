/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 08:30:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 10:13:27 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

#define SINGLE 0
#define DOUBLE 1

void		ft_upd_qstate(char c, int *in_squote, int *in_dquote);

static int	get_var_name_length(const char *str, int start)
{
	int	i;

	i = 0;
	if (str[start] == '?')
		return (1);
	while (str[start + i] && (ft_isalnum(str[start + i])
			|| str[start + i] == '_'))
		i++;
	return (i);
}

static char	*get_var_value(t_minishell *ms, const char *var_name)
{
	t_env	*env_var;

	if (!ft_strncmp(var_name, "?", 1))
		return (ft_itoa(ms->exit_status));
	env_var = ft_env_find(ms->envs, (char *)var_name);
	if (!env_var)
		env_var = ft_env_find(ms->vars, (char *)var_name);
	if (env_var)
		return (ft_strdup(env_var->value));
	else
		return (ft_strdup(""));
}

static char	*replace_variable(t_minishell *ms, char *str, int dollar_pos,
		int var_len)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	char	*front_substr;
	char	*back_substr;

	var_name = ft_substr(str, dollar_pos + 1, var_len);
	var_value = get_var_value(ms, var_name);
	free(var_name);
	front_substr = ft_substr(str, 0, dollar_pos);
	result = ms_strnjoin(front_substr, var_value, ft_strlen(var_value));
	free(var_value);
	back_substr = ft_strdup(str + dollar_pos + var_len + 1);
	result = ms_strnjoin(result, back_substr, ft_strlen(back_substr));
	free(back_substr);
	free(str);
	return (result);
}

char	*ms_expand_variable(t_minishell *ms, char *str, int *changed)
{
	int	i;
	int	in_quotes[2];
	int	var_len;

	i = 0;
	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
	while (str[i])
	{
		ft_upd_qstate(str[i], &(in_quotes[SINGLE]), &(in_quotes[DOUBLE]));
		if (str[i] == '$' && !(in_quotes[SINGLE]) && str[i + 1])
		{
			if (str[i + 1] == '?')
				var_len = 1;
			else
				var_len = get_var_name_length(str, i + 1);
			if (var_len > 0)
			{
				*changed = 1;
				return (replace_variable(ms, str, i, var_len));
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

	result = *line;
	changed = 1;
	while (changed)
	{
		changed = 0;
		result = ms_expand_variable(ms, result, &changed);
	}
	*line = result;
}
