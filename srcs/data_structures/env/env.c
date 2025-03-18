/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:51:41 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/18 11:06:21 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/env.h"
#include "../../../libft/includes/libft.h"
#include <stdlib.h>

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = (t_env *) malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->name = ft_strdup(name);
	if (!new_env->name)
	{
		free (new_env);
		return (NULL);
	}
	new_env->value = ft_strdup(value);
	if (!new_env->value)
	{
		free (new_env->name);
		free (new_env);
		return (NULL);
	}
	new_env->next = NULL;
	return (new_env);
}

void	ft_env_destroy(t_env *envs)
{
	t_env	*tmp;

	if (!envs)
		return ;
	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		free (tmp->name);
		free (tmp->value);
		free (tmp);
	}
}
