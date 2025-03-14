/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:35:42 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/13 15:39:04 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*ft_ast_insertnode(t_node *ast, t_node *new_node)
{
	t_node	*tmp;

	if (!ast)
		return (new_node);
	if (new_node->priority > ast->priority)
	{
		ast->right = ft_ast_insertnode(ast->right, new_node);
		return (ast);
	}
	else
	{
		new_node->left = ast;
		return (new_node);
	}
}

void	ft_ast_addleft(t_node *ast, t_node *node)
{
	if (ast)
		ast->left = node;
}

void	ft_ast_addright(t_node *ast, t_node *node)
{
	if (ast)
		ast->right = node;
}
