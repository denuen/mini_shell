/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:55:37 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/04 14:40:38 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_pwd(t_node *node)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_output(path);
		write(1, "\n", 1);
		return (0);
	}
	write(1, "\n", 1);
	ft_output_error(node->cmd[0], " ");
	return (-1);
}
