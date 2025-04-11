/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:09 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/11 16:30:59 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_cd(t_node *node, t_minishell *ms)
{
	t_env	*home;
	static char	*previous = NULL;
	char		*temp;
	sgl = 0;
	
	if (ft_strncmp(node->cmd[1], "-", 2) == 0)
	{
		temp = previous;
		previous = getcwd(NULL, 0);
		if (temp != NULL)
			ft_printf("%s\n", temp);
		chdir(temp);
		return (0);	
	}
	if (!node->cmd[1])
	{
		home = ft_env_find(ms->envs, "HOME");
		if (home)
		{
			previous = getcwd(NULL, 0);
			if (chdir(home->value) != -1)
				return (0);
		}
		return (0);
	}
	previous = getcwd(NULL, 0);
	if (chdir(node->cmd[1]) != -1)
		return (0);
	previous = NULL;
	ft_output_error(node->cmd[0], node->cmd[1]);
	sgl = 1;
	return (-1);
}
