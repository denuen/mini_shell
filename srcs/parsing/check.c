/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/09 16:44:03 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* TODO:
* this function should handle the entire
* line and parse it adding each cmd/op/redir in the
* correct node
*/
t_node	*ms_parse_input(const char *line)
{
	t_node	*ast;

	ms_validate_line(&ast, line);
}

int	ms_isvalid(const char *s)
{
	//TODO: utility for ms_check_cmd
}

int	ms_check_cmd(const char **line)
{
	t_node	*ast;
	char	**tmp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ms_iscmd(line[i]) && !ms_isvalid(line[i]))
			return (ms_invalidcmd(line[i]));
		i++;
		while (!ms_iscmd(line[i]))
		{
			if (!ms_isvalid(line[i]))
				return (ms_invalidcmd(line[i]));
			i++;
		}
	}
}

void	ms_validate_line(t_node **ast, const char *line)
{
	t_node	*ast;
	char	**split;
	int		i;
	int		j;

	i = 0;
	split = ft_split(line, ' ');
	while (split[i] != NULL)
	{
		j = 0;
		ms_check_cmd(split[i]);
		//TODO: allocate command line in ast and handle
		//the remain input, checking if it is valid
	}
}
