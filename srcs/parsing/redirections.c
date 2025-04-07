/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:49:41 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 15:00:20 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

static char	**ft_assignredir(char **split, int start, int *tokens)
{
	char	**redir;

	if (!split || !tokens)
		return (NULL);
	*tokens = 1;
	while (split[start + *tokens] && !ms_isop(split[start + *tokens])
		&& !ms_isredir(split[start + *tokens]))
		(*tokens)++;
	redir = (char **)malloc(sizeof(char *) * (*tokens + 1));
	if (!redir)
		return (NULL);
	redir[0] = ft_strdup(split[start]);
	if (!redir[0])
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

int	ms_validate_redir(t_minishell *ms, char **split, int *i)
{
	char	**redir;
	int		tokens;
	int		j;

	if (!split || !i || !ms)
		return (0);
	if (!ms_isredir(split[*i]))
		return (0);
	redir = ft_assignredir(split, *i, &tokens);
	if (!redir)
		return (0);
	j = 1;
	while (j < tokens)
	{
		redir[j] = ft_strdup(split[*i + j]);
		if (!redir[j])
			return (ft_matrix_destroy((void **)redir));
		j++;
	}
	redir[tokens] = NULL;
	*i += tokens;
	// ft_printf("Redir: ");
	// for(int j = 0; redir[j] != NULL; j++)
	// {
	// 	ft_printf("%s ", redir[j]);
	// }
	// ft_printf("\n");
	ms->ast = ft_ast_insertnode(ms->ast, ft_ast_newredir(redir));
	return (1);
}
