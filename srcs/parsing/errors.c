/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:58 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/14 12:31:52 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ft_matrix_destroy(void **ptr)
{
	unsigned char	**p;
	int				i;

	if (!ptr)
		return (0);
	p = (unsigned char **)ptr;
	i = 0;
	while (p[i])
	{
		if (p[i])
			free(p[i]);
		i++;
	}
	free(p);
	return (0);
}

int	ft_input_error(char *line, char **split, t_node *ast, int i)
{
	if (ms_isredir(split[i]) || ms_isop(split[i]))
		ft_printf("sintax error in '%s'", split[i]);
	else
		ft_printf("Command '%s' not found.\n", split[0]);
	if (line)
		free(line);
	ft_matrix_destroy((void **)split);
	ft_ast_destroy(ast);
	return (0);
}

void	ms_error(t_node *ast)
{
	ft_ast_destroy(ast);
	exit(EXIT_FAILURE);
}
