/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:55:37 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/08 10:51:15 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_pwd(t_node *node)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
		sgl = 0;
		return (0);
	}
	write(1, "\n", 1);
	ft_output_error(node->cmd[0], " ");
	sgl = 1;
	free(path);
	return (-1);
}
