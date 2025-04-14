/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:20:54 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:26:48 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_or_exec(t_node *left, t_node *right, t_minishell *ms)
{
	if (sgl == 0)
		sgl = ms_executor(left, ms);
	if (sgl != 0)
		sgl = ms_executor(right, ms);
	return (sgl);
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
	sgl = ms_executor(right, ms);
	wait(&status);
	status = WEXITSTATUS(status);
	return (sgl);
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
		sgl = ms_executor(left, ms);
		exit(sgl);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(&sgl);
	sgl = WEXITSTATUS(sgl);
	if (sgl == 0)
		sgl = ms_executor(right, ms);
	dup2(saved, STDIN_FILENO);
	close(saved);
	return (sgl);
}

int	ms_and_operator(t_node *left, t_node *right, t_minishell *ms)
{
	pid_t	pid;

	sgl = 0;
	pid = fork();
	if (pid == 0)
	{
		sgl = ms_executor(left, ms);
		exit(sgl);
	}
	wait(&sgl);
	sgl = WEXITSTATUS(sgl);
	if (sgl == 0)
		sgl = ms_executor(right, ms);
	return (sgl);
}
