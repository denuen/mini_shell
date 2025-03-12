/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:38:19 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/12 16:59:35 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_tofile_exec(t_node *left, t_node *right)
{
	int	fd;
	pid_t	pid;

	//controlla se il file esiste con access magari
	pid = fork();
	if (pid == 0)
	{
		fd = open(right->redir, O_WRONLY | O_TRUNC );
		dup2(fd, STDOUT_FILENO);
		ms_executor(left);
		close(fd);
	}
	return (1);
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
		//controlla se il file esiste se fd è minore di 0
		dup2(fd, STDIN_FILENO);
		status = ms_executor(left);
		close(fd);
		exit(status);
	}
	wait(&status);
	status = WEXITSTATUS(status);
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
		//controlla se il file esiste se fd è minore di 0
		dup2(fd, STDOUT_FILENO);
		status = ms_executor(left);
		close(fd);
		exit(status);
	}
	wait(&status);
	status = WEXITSTATUS(status);
	return (status);
}