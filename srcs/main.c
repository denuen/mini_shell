/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:52:23 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/18 16:04:17 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*line;

	//Check iniziali, su argc e argv
	ms.envs = ft_get_envs(envp);
	ms.vars = NULL;
	readline(line);
	while (line)
	{
		ms_validate_line(&ms, line);
		free (line);
		readline(line);
	}
}
