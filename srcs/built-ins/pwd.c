/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:55:37 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/10 16:14:45 by ahabdelr         ###   ########.fr       */
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
		return (0);
	}
	ft_output_error(node->cmd[0], " ");
	return (1);
}