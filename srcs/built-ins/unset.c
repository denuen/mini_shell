/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:50:16 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/14 13:51:52 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_unset(t_node *node, t_minishell *ms)
{
	t_env	*tmp;
	int		i;

	g_sgl = 0;
	if (!node || !ms)
	{
		g_sgl = 1;
		return (0);
	}
	if (!node->cmd[1])
		return (1);
	i = 0;
	while (node->cmd[++i])
	{
		tmp = ft_env_find(ms->envs, node->cmd[i]);
		if (tmp)
			ft_env_remove(&(ms->envs), node->cmd[i]);
		else
		{
			tmp = ft_env_find(ms->vars, node->cmd[i]);
			if (tmp)
				ft_env_remove(&(ms->vars), node->cmd[i]);
		}
	}
	return (1);
}
