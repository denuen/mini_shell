/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:52:23 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/03 15:35:19 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int sgl;

int main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*line;

	(void)argc;
	(void)argv;
	line = NULL;
	sgl = 0;
	// Check iniziali, su argc e argv
	ms.envs = ft_get_envs(envp);
	ms.vars = NULL;

	line = readline("scrivi> ");
	ft_printf("\n");
	while (line)
	{
		ms_validate_line(&ms, line);
		ms_executor(ms.ast, &ms);
		line = NULL;
		ft_printf("\n");
		line = readline("scrivi> ");
	}
	ft_ast_destroy(ms.ast);
	ft_env_destroy(ms.envs);
	ft_env_destroy(ms.vars);
}
