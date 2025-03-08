/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:37:22 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/08 19:51:23 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
//the node is going to have inside an array of strigs, the first one is going to be
// the function itself, while the other ones are going to be printable strings.

int	ms_echo(t_node *node)
{
	int	i;
	int	type;

	i = 1;
	type == ft_strncmp(node.cmd[0], "-n", 2);
	while (i != '\0')
	{
		ft_printf("%s", node.cmd[i]);
		i++;
	}
	if (type != 0)
		write(1, "\n", 1);
	return (0);
}
