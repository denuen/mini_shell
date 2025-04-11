/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:37:22 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/08 15:17:48 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_echo(t_node *node)
{
	int	i;
	int	type;

	i = 1;
	sgl = 0;
	type = ft_strncmp(node->cmd[1], "-n", 2);
	if (type == 0)
		i++;
	while (node->cmd[i])
	{
		if ((type != 0 && i > 1 ) || (type  == 0 && i > 2))
			write(1, " ", 1);
		ft_printf("%s", node->cmd[i]);
		i++;
	}
	if (type != 0)
		write(1, "\n", 1);
	sgl = 0;
	return (0);
}
