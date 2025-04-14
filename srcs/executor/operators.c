/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:20:54 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:53:23 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_or_exec(t_node *left, t_node *right, t_minishell *ms)
{
	if (g_sgl == 0)
		g_sgl = ms_executor(left, ms);
	if (g_sgl != 0)
		g_sgl = ms_executor(right, ms);
	return (g_sgl);
}

int	ms_bg_exec(t_node *left, t_node *right, t_minishell *ms)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		status = ms_executor(left, ms);
		exit(status);
	}
	g_sgl = ms_executor(right, ms);
	wait(&status);
	status = WEXITSTATUS(status);
	return (g_sgl);
}

int	ms_pipe_exec(t_node *left, t_node *right, t_minishell *ms)
{
	int		pipefd[2];
	pid_t	pid;
	int		saved;

	saved = dup(STDIN_FILENO);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		g_sgl = ms_executor(left, ms);
		exit(g_sgl);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(&g_sgl);
	g_sgl = WEXITSTATUS(g_sgl);
	if (g_sgl == 0)
		g_sgl = ms_executor(right, ms);
	dup2(saved, STDIN_FILENO);
	close(saved);
	return (g_sgl);
}

int	ms_and_operator(t_node *left, t_node *right, t_minishell *ms)
{
	pid_t	pid;

	g_sgl = 0;
	pid = fork();
	if (pid == 0)
	{
		g_sgl = ms_executor(left, ms);
		exit(g_sgl);
	}
	wait(&g_sgl);
	g_sgl = WEXITSTATUS(g_sgl);
	if (g_sgl == 0)
		g_sgl = ms_executor(right, ms);
	return (g_sgl);
}
