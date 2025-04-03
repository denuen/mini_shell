/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:05:35 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/04 00:27:13 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/env.h"
#include "../../../libft/includes/libft.h"
#include <stdlib.h>

void	ft_env_addordered(t_env **envs, t_env *new_env)
{
	t_env	*current;
	t_env	*prev;

	if (!envs || !new_env)
		return ;
	if (!*envs)
	{
		*envs = new_env;
		return ;
	}
	current = *envs;
	prev = NULL;
	while (current && ft_strncmp(current->name, new_env->name, \
	ft_strlen(new_env->name)) < 0)
	{
		prev = current;
		current = current->next;
	}
	new_env->next = current;
	if (prev)
		prev->next = new_env;
	else
		*envs = new_env;
}

void	ft_env_addback(t_env **envs, t_env *new_env)
{
	t_env	*tmp;

	if (!envs)
		return ;
	if (!*envs)
		*envs = new_env;
	else
	{
		tmp = *envs;
		while ((*envs)->next)
			(*envs) = (*envs)->next;
		(*envs)->next = new_env;
		(*envs) = tmp;
	}
}

t_env	*ft_env_find(t_env *envs, char *name)
{
	t_env	*tmp;

	if (!envs || !name)
		return (NULL);
	tmp = envs;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_env_print(t_env *envs)
{
	t_env	*tmp;

	if (!envs)
	{
		ft_printf("No variables allocated.\n");
		return ;
	}
	tmp = envs;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_env_remove(t_env **envs, char *name)
{
	t_env	*lst;
	t_env	*prev;

	if (!envs || !*envs || !name)
		return ;
	lst = *envs;
	prev = NULL;
	if (!ft_strncmp(lst->name, name, ft_strlen(name) + 1))
		*envs = lst->next;
	else
	{
		while (lst && ft_strncmp(lst->name, name, ft_strlen(name) + 1))
		{
			prev = lst;
			lst = lst->next;
		}
		if (!lst)
			return ;
		prev->next = lst->next;
	}
	free(lst->name);
	free(lst->value);
	free(lst);
}
