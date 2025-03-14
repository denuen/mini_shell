/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:49:17 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/14 12:30:39 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_validate_op(char **split, t_node **ast, int *i)
{
	char	*op;
	int		cnt;
	int		j;

	if (!split || !ast || !i)
		return (0);
	if (!ms_isop(split[*i]))
		return (1);
	cnt = 0;
	j = *i;
	while (split[j] && ms_isop(split[j]))
	{
		cnt++;
		j++;
	}
	if (cnt > 1)
		return (0);
	op = ft_strdup(split[*i]);
	if (!op)
		return (0);
	*i += 1;
	ft_ast_insertnode(ast, ft_ast_newop(op));
	return (1);
}
