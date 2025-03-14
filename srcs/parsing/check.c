/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/14 10:57:17 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

/*
* TODO:
* this function should handle the entire
* line and parse it adding each cmd/op/redir in the
* correct node
*/
void	ms_validate_line(t_node **ast, char *line)
{
	t_node	*new_node;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(line, ' ');
	while (split[i] != NULL)
	{
		if (!ms_validate_cmd(split, ast, &i)
			|| !ms_validate_op(split, ast, &i)
			|| !ms_validate_redir(split, ast, &i))
			ft_input_error(line, split, ast, i);
	}
	ft_matrix_destroy(split);
	free (line);
}
