/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:09 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/12 13:26:07 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_cd(t_node *node)
{
	if (chdir(node->cmd[1]) != -1)
	{
		ft_output(node->cmd[1]);
		return (0);
	}
	ft_output_error(node->cmd[0], node->cmd[1]);
	return (-1);
}