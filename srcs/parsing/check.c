/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/18 15:10:53 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

static char	*ft_get_vars(char **split)
{
}

void	ms_validate_line(t_minishell *ms, char *line)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	ms->vars = ft_get_vars(split);
	split = ft_rearrange_line(ms, split);
	while (split[i])
	{
		if (ms_validate_cmd(&ms, split, &i))
			continue ;
		else if (ms_validate_redir(&ms, split, &i))
			continue ;
		else if (ms_validate_op(&ms, split, &i))
			continue ;
		else
			ft_input_error(line, ms, split, i);
	}
	ft_matrix_destroy(split);
	free(line);
}
