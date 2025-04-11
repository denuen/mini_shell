/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:09 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/07 12:04:40 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_cd(t_node *node)
{
	sgl = 0;
	if (!node->cmd[1])
	{
		write(1, "I told you only RELATIVE or ABSOLUTE path\n", 43);
		sgl = 1;
		return (-1);
	}
	if (chdir(node->cmd[1]) != -1)
		return (0);
	ft_output_error(node->cmd[0], node->cmd[1]);
	sgl = 1;
	return (-1);
}
