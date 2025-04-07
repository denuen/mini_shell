/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:35:42 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 11:41:38 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ast.h"

t_node	*ft_ast_insertnode(t_node *ast, t_node *new_node)
{
	if (!ast)
		return (new_node);
	if (new_node->priority < ast->priority)
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

// void	ft_ast_update_env(t_node *ast, t_env *env, int flag)
// {
// 	if (ast->left)
// 		ft_ast_update_env(ast->left, env, flag);
// 	if (ast->right)
// 		ft_ast_update_env(ast->right, env, flag);
// 	if (flag == ENVS)
// 		ast->envs = env;
// 	else if (flag == VARS)
// 		ast->vars = env;
// }
