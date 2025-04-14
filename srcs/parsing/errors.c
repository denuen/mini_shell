/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:58 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/14 13:54:23 by marvin@42.f      ###   ########.fr       */
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
	p = NULL;
	return (0);
}

void	ft_input_error(t_minishell *ms, char **split, int i)
{
	if (ms_isredir(split[i]) || ms_isop(split[i]))
	{
		ft_printf("minishell: syntax error near \
unexpected token '%s'\n", split[i]);
	}
	else
	{
		ft_printf("minishell: command not found: '%s'\n", split[i]);
		g_sgl = 127;
		ms->exit_status = g_sgl;
	}
}
