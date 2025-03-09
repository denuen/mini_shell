/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:35:42 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/09 16:43:20 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
