/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:15:17 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/10 18:32:04 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//dalla chiamata di esecuzione principale controllo di che genere sia il nodo
// se il nodo è una pipe allora lancio pipe_execute(left, right);
//  se il nodo è un comando allora lancio command_execute(node);
//   se il nodo è un redirection allora lancio redirection_execute(node);
// ciò dovrebbe aprirsi in maniera pseudo-ricorsiva distendendosi fino alla fine dell'ABS

int	ms_executor(t_node *node)
{
	//setting up recursivity (cleaning fds)
	if (node->type == COMMAND)
		//execute built in
	else if (node->type == OPERATOR)
		//execute operator
	else if (node->type == REDIRECTION)
		//execute redirection
}