/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:14:35 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/17 17:40:00 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export_add(t_env *new, t_node *node)
{
	t_env	*current;

	current = node->env;
	if (current == NULL || ft_strncmp(current->name, new->name, 1000) > 0)
	{
		new->next = current;
		node->env = new;
		return (0);
	}
	while (current->next && ft_strncmp(current->next->name, new->name, 1000) > 0)
	{
		if (ft_strncmp(current->next->name, new->name, 1000) == 0)
		{
			new->next = current->next->next;
			current->next = new;
			return (0);
		}
		current = current->next;
	}
	new->next = current->next;
	current->next = new;
	return (0);
}

int	ft_export_var(char *search, t_node *node)
{
	t_env	*current;

	current = node->var;
	while (current && ft_strncmp(search, current->name, 1000) != 0)
		current = current->next;
	if (current)
		ft_export_add(current, node);
	else
	{
		current = (t_env *)malloc(sizeof(t_env));
		current->name = search;
		current->value = NULL;
		ft_export_add(current, node);
	}
	return (0);
}

int	ft_export_print(t_node *node)
{
	t_env	*current;

	current = node->env;
	while (current != NULL)
	{
		ft_printf("%s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

int	ft_get_string(t_env *new, t_node *node)
{
// da gestire A) con virgolette, B) senza virgolette
}

int	ms_export(t_node *node)
{
	t_env	new;

	if (node->cmd[1] == NULL)
		return  (ft_export_print(node));
	else if (!ft_strchr(node->cmd[1], '='))
		return (ft_export_var(node->cmd[1], node));
	else
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (ft_get_string(*new, node))
			return (ft_export_add(new, node));
	}

}