/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:09 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:33:21 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_go_home(t_minishell *ms, char **previous)
{
	t_env	*home;

	home = ft_env_find(ms->envs, "HOME");
	if (home)
	{
		*previous = getcwd(NULL, 0);
		chdir(home->value);
		return (0);
	}
	return (0);
}

int	ms_cd(t_node *node, t_minishell *ms)
{
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
		return (ms_go_home(ms, &previous));
	previous = getcwd(NULL, 0);
	if (chdir(node->cmd[1]) != -1)
		return (0);
	previous = NULL;
	ft_output_error(node->cmd[0], node->cmd[1]);
	sgl = 1;
	return (-1);
}
