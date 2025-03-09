/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:05 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/09 16:43:35 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include <stdlib.h>

t_node	*ft_ast_newcommand(char **cmd)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = COMMAND;
	new_node->cmd = cmd;
	new_node->op = NULL;
	new_node->redir = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

t_node	*ft_ast_newop(char *op)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = OPERATOR;
	new_node->op = op;
	new_node->cmd = NULL;
	new_node->redir = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

t_node	*ft_ast_newredir(char *redir)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = REDIRECTION;
	new_node->redir = redir;
	new_node->cmd = NULL;
	new_node->op = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

void	ft_ast_destroy(t_node *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	if (node->left)
		ft_ast_destroy(node->left);
	if (node->right)
		ft_ast_destroy(node->right);
	if (node->type == COMMAND)
	{
		while (node->cmd[i] != NULL)
		{
			free (node->cmd[i]);
			i++;
		}
		free (node->cmd);
	}
	else if (node->type == OPERATOR)
		free (node->op);
	else if (node->type == REDIRECTION)
		free (node->redir);
}

/********************** Debugging zone **********************/

void	ft_ast_printtree(t_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->left)
		ft_ast_printtree(node->left);
	if (node->right)
		ft_ast_printtree(node->right);
	if (node->type == COMMAND)
		ft_ast_printcmd(node);
	else if (node->type == OPERATOR)
		ft_printf("Operator: %s\n", node->op);
	else if (node->type == REDIRECTION)
		ft_printf("Redirection: %s\n", node->redir);
}

void	ft_ast_printcmd(t_node *node)
{
	int	i;

	if (!node || node->type != COMMAND)
		return ;
	if (node->cmd)
	{
		i = 0;
		if (node->cmd[i])
		{
			ft_printf("Command: ");
			while (node->cmd[i + 1] != NULL)
			{
				ft_printf("%s ", node->cmd[i]);
				i++;
			}
			ft_printf("%s\n", node->cmd[i]);
		}
	}
}

int	ft_ast_size(t_node *node)
{
	if (!node)
		return (0);
	return (1 + ft_ast_size(node->left) \
			+ ft_ast_size(node->right));
}
