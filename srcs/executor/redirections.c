/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:38:19 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/13 15:37:57 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_tofile_exec(t_node *left, t_node *right)
{
	int	fd;
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir, O_WRONLY | O_TRUNC );
		if (fd < 0)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		status = ms_executor(left);
		close(fd);
		exit(status);
	}
	wait(&status);
	close(fd);
	status = WEXITSTATUS(status);
	return (status);
}

int	ms_fromfile_exec(t_node *left, t_node *right)
{
	int	fd;
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir, O_RDONLY);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDIN_FILENO);
		status = ms_executor(left);
		close(fd);
		exit(status);
	}
	wait(&status);
	status = WEXITSTATUS(status);
	close(fd);
	return (status);
}

int	ms_appen_exec(t_node *left, t_node *right)
{
	pid_t	pid;
	int	status;
	int	fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir, O_APPEND);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		status = ms_executor(left);
		close(fd);
		exit(status);
	}
	wait(&status);
	status = WEXITSTATUS(status);
	close(fd);
	return (status);
}

int	ms_heredoc_exec(t_node *left, t_node *right)
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
		write(1, &right->redir, ft_strlen(right->redir));
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		status = ms_executor(left);
	}
	return (status);
}