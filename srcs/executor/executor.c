/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:15:17 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/19 14:27:13 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_operator_exec(t_node *node, t_minishell *ms)
{
	int	status;

	if (node->op == "|")
		status = ms_pipe_exec(node->left, node->right, ms);
	else if (node->op == "||")
		status = ms_or_exec(node->left, node->right, ms);
	else if (node->op == "&")
		status = ms_bg_exec(node->left, node->right, ms);
	else if (node->op == "&&")
		status = ms_and_exec(node->left, node->right, ms);
}

int	ft_redirection_exec(t_node *node, t_minishell *ms)
{
	int	status;

	if (node->redir == ">")
		status = ms_tofile_exec(node->left, node->right, ms);
	else if (node->redir == "<")
		status = ms_fromfile_exec(node->left, node->right, ms);
	else if (node->redir == ">>")
		status = ms_append_exec(node->left, node->right, ms);
	else if (node->redir == "<<")
		status = ms_heredoc_exec(node->left, node->right, ms);
}

int	ms_extern(t_node *node, t_minishell *ms)
{
	int	status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strlen_arr(node->cmd) == 2)
			execve(node->cmd[0], &node->cmd[1], environ);
		else
			execve(node->cmd[0], NULL, environ);
		perror("Error executing command");
		exit(-1);
	}
	wait(&status);
	status = WEXITSTATUS(status);
	return (status);
}
//gestito quelle inserite tramite aboslute path, adesso bisogna fare il path finder e cercare quelle inserite senza contesto come grep cat ecc...

int	ft_commmand_exec(t_node *node, t_minishell *ms)
{
	int	status;

	if (node->cmd[0] == "cd")
		status = ms_cd(node, ms);
	else if (node->cmd[0] == "echo")
		status = ms_echo(node, ms);
	else if (node->cmd[0] == "pwd")
		status = ms_pwd(node, ms);
	else
		status = ms_extern(node, ms);
	return (status);
}

int	ms_executor(t_node *node, t_minishell *ms)
{
	int	status;
	//setting up recursivity (cleaning fds)

	if (node->type == COMMAND)
		status = ft_commmand_exec(node, ms);
	else if (node->type == OPERATOR)
		status = ft_operator_exec(node, ms);
	else if (node->type == REDIRECTION)
		status = ft_redirection_exec(node, ms);
	return (status);
}