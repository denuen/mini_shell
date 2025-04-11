/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:49:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 10:10:29 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	ft_upd_qstate(char c, int *in_squotes, int *in_dquotes)
{
	if (c == '\'' && !(*in_dquotes))
		*in_squotes = !(*in_squotes);
	if (c == '"' && !(*in_squotes))
		*in_dquotes = !(*in_dquotes);
}

void	ft_remove_quotes(char **str)
{
	t_utils	u;
	char	*result;

	if (!str || !*str || (!ft_strchr(*str, '\'') && !ft_strchr(*str, '"')))
		return ;
	result = ft_calloc(ft_strlen(*str) + 1, sizeof(char));
	u.i = -1;
	u.j = 0;
	u.squote = 0;
	u.dquote = 0;
	while ((*str)[++(u.i)])
	{
		if (((*str)[(u.i)] == '\'' && !u.dquote)
				|| ((*str)[(u.i)] == '"' && !u.squote))
		{
			if ((*str)[(u.i)] == '\'')
				u.squote = !u.squote;
			else
				u.dquote = !u.dquote;
		}
		else
			result[(u.j)++] = (*str)[(u.i)];
	}
	free((*str));
	*str = result;
}
