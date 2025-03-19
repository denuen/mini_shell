/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:37:22 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/19 10:58:06 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_echo(t_node *node, t_minishell *ms)
{
	int	i;
	int	type;

	i = 1;
	type == ft_strncmp(node->cmd[0], "-n", 2);
	while (i != '\0')
	{
		ft_printf("%s", node->cmd[i]);
		i++;
	}
	if (type != 0)
		write(1, "\n", 1);
	return (0);
}
