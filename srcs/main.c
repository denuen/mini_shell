/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:52:23 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/10 15:09:53 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int	sgl;
int signal_receiver(t_minishell *ms);

static void	ms_init(t_minishell *ms)
{
	ms->ast = NULL;
	ms->envs = ft_get_envs();
	ms->vars = NULL;
	ms->exit_status = 0;
	sgl = 0;
}

void	ms_destroy(t_minishell *ms)
{
	if (ms->ast)
	{
		ft_ast_destroy(ms->ast);
		ms->ast = NULL;
	}
	if (ms->envs)
	{
		ft_env_destroy(ms->envs);
		ms->envs = NULL;
	}
	if (ms->vars)
	{
		ft_env_destroy(ms->vars);
		ms->vars = NULL;
	}
}

static void	ms_process_line(t_minishell *ms, char *line)
{
	if (ms->ast)
	{
		ft_ast_destroy(ms->ast);
		ms->ast = NULL;
	}
	ms_validate_line(ms, line);
	if (ms->ast)
		ms_executor(ms->ast, ms);
	if (ms->ast)
	{
		ft_ast_destroy(ms->ast);
		ms->ast = NULL;
	}
}

int	main(void)
{
	t_minishell	ms;
	char		*line;

	ms_init(&ms);
	while (1)
	{
		sgl_still(&ms);
		line = readline("minishell$ ");
		sgl_moving(&ms);
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strlen(line) > 0)
		{
			sgl = 0;
			ms_process_line(&ms, line);
		}
		else
			free(line);
	}
	ms_destroy(&ms);
	return (0);
}
