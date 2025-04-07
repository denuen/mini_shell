/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:52:23 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 10:29:34 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int	sgl;

static void	ms_init(t_minishell *ms, char **envp)
{
	ms->ast = NULL;
	ms->envs = ft_get_envs(envp);
	ms->vars = NULL;
	sgl = 0;
}

static void	ms_destroy(t_minishell *ms)
{
	if (ms->ast)
		ft_ast_destroy(ms->ast);
	ft_env_destroy(ms->envs);
	ft_env_destroy(ms->vars);
}

static void	ms_process_line(t_minishell *ms, char *line)
{
	if (ms->ast)
	{
		ft_ast_destroy(ms->ast);
		ms->ast = NULL;
	}
	ms_validate_line(ms, line);
	if (ms->ast == NULL)
		ft_printf("minishell: syntax error\n");
	else
		ms_executor(ms->ast, ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*line;

	(void)argc;
	(void)argv;
	ms_init(&ms, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		ms_process_line(&ms, line);
	}
	ms_destroy(&ms);
	return (0);
}
