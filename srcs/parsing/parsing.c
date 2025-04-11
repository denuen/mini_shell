/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 14:23:45 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

char	**ft_rearrange_line(t_minishell *ms, char **split);

static void	ft_get_vars(t_minishell *ms, char **split, int *i)
{
	t_env	*new_var;
	t_env	tmp;
	int		divisor;

	if (!ms || !split)
		return ;
	while (split[*i])
	{
		divisor = ft_findchr(split[*i], '=');
		if (divisor < 0)
			break ;
		tmp.name = ft_substr(split[*i], 0, divisor);
		tmp.value = ft_strdup(&split[*i][divisor + 1]);
		new_var = ft_new_env(tmp.name, tmp.value);
		if (new_var)
			ft_env_addordered(&ms->vars, new_var);
		free(tmp.name);
		free(tmp.value);
		(*i)++;
	}
}

void	ms_validate_line(t_minishell *ms, char *line)
{
	char	**split;
	int		i;

	i = 0;
	split = ms_split(line, ' ', ms);
	ft_get_vars(ms, split, &i);
	while (split[i])
	{
		if (ms_validate_cmd(ms, split, &i))
			continue ;
		else if (ms_validate_redir(ms, split, &i))
			continue ;
		else if (ms_validate_op(ms, split, &i))
			continue ;
		else
		{
			ft_input_error(ms, split, i);
			ft_ast_destroy(ms->ast);
			ms->ast = NULL;
			break ;
		}
	}
	ft_matrix_destroy((void **)split);
}
