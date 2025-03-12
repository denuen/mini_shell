/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:48:31 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/13 00:20:16 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	*ft_ssdestroy(char **ss);

int	ms_validate_cmd(char **line, t_node **ast, int *i)
{
	t_node		*cmd_node;
	char		*cmd_line;
	char		**cmd;
	int			i;

	if (!line)
		return (0);
	i = 0;
	cmd = (char **)malloc(sizeof(char *) * ft_strlen(line));
	cmd[ft_strlen(line)] = NULL;
	if (!ms_isbuiltin(line[*i]))
		cmd[0] = ms_isexecutable(line[*i]);
	else
		cmd[0] = line[*i];
	if (!cmd)
		return (ft_ssdestroy(cmd));
	*i += 1;
	while (!ms_isop(line[*i]) && !ms_isredir(line[*i]))
	{
		cmd[*i] = ft_strdup(line[*i]);
		(*i)++;
	}
	(*ast)->left = ft_ast_newcommand(cmd);
	return (0);
}
