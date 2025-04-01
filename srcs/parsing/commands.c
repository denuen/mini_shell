/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:48:31 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/01 15:33:29 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_assigncmd_args(char **split, int start, int tokens, char ***cmd)
{
	int	i;

	i = 1;
	if (!split || !cmd || !(*cmd))
		return ;
	while (i < tokens)
	{
		(*cmd)[i] = ft_strdup(split[start + i]);
		if (!(*cmd)[i])
		{
			ft_matrix_destroy((*cmd));
			(*cmd) = NULL;
			break ;
		}
		i++;
	}
}

static char	**ft_assigncmd(char **split, int start, int *tokens)
{
	char	**cmd;
	int		j;

	if (!split || !tokens)
		return (NULL);
	*tokens = 1;
	while (split[start + *tokens] && !ms_isop(split[start + *tokens])
		&& !ms_isredir(split[start + *tokens]))
		(*tokens)++;
	cmd = (char **)malloc(sizeof(char *) * (*tokens + 1));
	if (!cmd)
		return (NULL);
	cmd[*tokens] = NULL;
	if (!ms_isbuiltin(split[start]))
		cmd[0] = ms_isexecutable(split[start]);
	else
		cmd[0] = ft_strdup(split[start]);
	if (!cmd[0])
	{
		free(cmd);
		return (NULL);
	}
	ft_assigncmd_args(split, start, *tokens, &cmd);
	return (cmd);
}

int	ms_validate_cmd(t_minishell *ms, char **split, int *i)
{
	char	**cmd;
	int		tokens;

	if (!split || !ms || !i)
		return (0);
	cmd = ft_assigncmd(split, *i, &tokens);
	if (!cmd)
		return (0);
	*i += tokens;
	ms->ast = ft_ast_insertnode(ms->ast, ft_ast_newcommand(cmd));
	if (!ms->ast)
	{
		ft_matrix_destroy((void **)cmd);
		return (0);
	}
	return (1);
}
