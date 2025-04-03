/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:14:35 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/03 14:22:12 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env_arg(char *name, t_node *node, t_minishell *ms)
{
	t_env	*env;
	t_env	*var;

	env = ft_env_find(ms->envs, name);
	if (env)
	{
		if (node->cmd[2])
			env->value = node->cmd[2];
	}
	else
	{
		var = ft_env_find(ms->vars, name);
		if (var)
		{
			var = ft_new_env(var->name, var->value);
			ft_env_addordered(&ms->envs, var);
			return (0);
		}
		else
		{
			var = ft_new_env(name, node->cmd[2]);
			ft_env_addordered(&ms->envs, var);
		}
	}
	return (1);
}

int	ms_export(t_node *node, t_minishell *ms)
{
	if (node->cmd[1] == NULL)
		ft_env_print(ms->envs);
	else
		ft_env_arg(node->cmd[1], node, ms);
	return (0);
}
