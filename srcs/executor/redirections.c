/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:38:19 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/03 15:07:25 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_tofile_exec(t_node *left, t_node *right, t_minishell *ms)
{
	int	fd;
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		sig_check();
		status = ms_executor(left, ms);
		close(fd);
		exit(status);
	}
	wait(&status);
	sig_check();
	status = WEXITSTATUS(status);
	return (status);
}

int	ms_fromfile_exec(t_node *left, t_node *right, t_minishell *ms)
{
	int	fd;
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir[0], O_RDONLY);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDIN_FILENO);
		sig_check();
		status = ms_executor(left, ms);
		close(fd);
		exit(status);
	}
	wait(&status);
	sig_check();
	status = WEXITSTATUS(status);
	return (status);
}

int	ms_append_exec(t_node *left, t_node *right, t_minishell *ms)
{
	pid_t	pid;
	int	status;
	int	fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		sig_check();
		status = ms_executor(left, ms);
		exit(status);
	}
	wait(&status);
	status = WEXITSTATUS(status);
	sig_check();
	return (status);
}

int	ms_heredoc_exec(t_node *left, t_node *right, t_minishell *ms)
{
	int	status;
	pid_t	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		sig_check();
		write(STDOUT_FILENO, right->redir[0], ft_strlen(right->redir[0]));
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		sig_check();
		status = ms_executor(left, ms);
	}
	return (status);
}
