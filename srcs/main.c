/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:52:23 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/14 14:06:05 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

#define RED "\033[1;31m"
#define GREEN "\033[01;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

int			g_sgl;
int			signal_receiver(t_minishell *ms);

static void	ms_init(t_minishell *ms)
{
	ms->ast = NULL;
	ms->envs = ft_get_envs();
	ms->vars = NULL;
	ms->exit_status = 0;
	g_sgl = 0;
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

static void	ms_process_line(t_minishell *ms, char *line, int *sgl)
{
	*sgl = 0;
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

char	*ms_get_prompt(void)
{
	char	*cwd;
	char	*home;
	char	*path_display;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ms_strnjoin(GREEN, "minishell$: ", -1));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		path_display = ft_strjoin("~", cwd + ft_strlen(home));
	else
		path_display = ft_strdup(cwd);
	free(cwd);
	prompt = ft_strjoin(GREEN, "minishell");
	prompt = ms_strnjoin(prompt, RESET, -1);
	prompt = ms_strnjoin(prompt, ":", -1);
	prompt = ms_strnjoin(prompt, RESET, -1);
	prompt = ms_strnjoin(prompt, BLUE, -1);
	prompt = ms_strnjoin(prompt, path_display, -1);
	free(path_display);
	prompt = ms_strnjoin(prompt, RESET, -1);
	prompt = ms_strnjoin(prompt, "$ ", -1);
	prompt = ms_strnjoin(prompt, RESET, -1);
	return (prompt);
}

int	main(void)
{
	t_minishell	ms;
	char		*line;
	char		*prompt;

	ms_init(&ms);
	while (1)
	{
		sig_setter(&prompt);
		line = readline(prompt);
		if (!line)
		{
			write(1, "exit\n\n", 6);
			free(prompt);
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strlen(line) > 0)
			ms_process_line(&ms, line, &g_sgl);
		else
			free(line);
		free(prompt);
	}
	ms_destroy(&ms);
	return (0);
}
