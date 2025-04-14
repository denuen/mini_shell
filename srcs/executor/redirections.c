/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:38:19 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:54:08 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_tofile_exec(t_node *left, t_minishell *ms, char *file)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		g_sgl = ms_executor(left, ms);
		close(fd);
		exit(g_sgl);
	}
	wait(&g_sgl);
	g_sgl = WEXITSTATUS(g_sgl);
	return (g_sgl);
}

int	ms_fromfile_exec(t_node *left, t_minishell *ms, char *file)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			exit(-1);
		dup2(fd, STDIN_FILENO);
		g_sgl = ms_executor(left, ms);
		close(fd);
		exit(g_sgl);
	}
	wait(&g_sgl);
	g_sgl = WEXITSTATUS(g_sgl);
	return (g_sgl);
}

int	ms_append_exec(t_node *left, t_minishell *ms, char *file)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			g_sgl = -1;
		dup2(fd, STDOUT_FILENO);
		close(fd);
		g_sgl = ms_executor(left, ms);
		exit(g_sgl);
	}
	wait(&g_sgl);
	g_sgl = WEXITSTATUS(g_sgl);
	return (g_sgl);
}

int	ms_heredoc_exec(t_node *left, t_minishell *ms, char *file)
{
	pid_t	pid;
	int		fd[2];
	int		saved;

	pipe(fd);
	saved = dup(STDIN_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_printf("%s", file);
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		wait(&g_sgl);
		g_sgl = ms_executor(left, ms);
		dup2(saved, STDIN_FILENO);
	}
	return (g_sgl);
}
