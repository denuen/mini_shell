/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:20:54 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/24 09:01:23 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_or_exec(t_node *left, t_node *right, t_minishell *ms)
{
	int	status;

	status = ms_executor(left);
	if (status != 0)
		status = ms_executor(right);
	return (status);
}

int	ms_bg_exec(t_node *left, t_node *right, t_minishell *ms)
{
	pid_t	pid;
	int	status[2];

	status[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		status[0] = ms_executor(left);
		exit(status[0]);
	}
	status[1] = ms_executor(right);
	wait(&status[0]);
	status[0] = WEXITSTATUS(status[0]);
	return (status[0] + status[1]);
}

int	ms_pipe_exec(t_node *left, t_node *right, t_minishell *ms)
{
	int	pipefd[2];
	pid_t	pid;
	int	status[2];

	status[1] = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		status[0] = ms_executor(left);
		exit(status[0]);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(&status[0]);
	status[0] = WEXITSTATUS(status[0]);
	status[1] = ms_executor(right);
	return (status[1]);	
}

int	ms_and_operator(t_node *left, t_node *right, t_minishell *ms)
{
	pid_t	pid;
	int	status[2];

	status[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		status[0] = ms_executor(left);
		exit(status[0]);
	}
	wait(&status[0]);
	status[0] = WEXITSTATUS(status[0]);
	if (status[0] == 0)
		status[1] = ms_executor(right);
	if (status[1] == 1)
		status[1] = 0; //tutto ok, ancora da inserire che se ritorna 1 allora è un file
	return (status[0] + status[1]);
}