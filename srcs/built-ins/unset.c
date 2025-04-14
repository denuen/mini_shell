/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:50:16 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/14 13:27:49 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_unset(t_node *node, t_minishell *ms)
{
	t_env	*tmp;
	int		i;

	sgl = 0;
	if (!node || !ms)
	{
		sgl = 1;
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
