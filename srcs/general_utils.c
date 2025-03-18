/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:03 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/18 15:01:45 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

//It allocates a string of a certain size specified by 'n'
char	*ft_strndup(const char *s, int n)
{
	char	*new_s;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n > len)
		n = len;
	new_s = (char *) malloc(sizeof(char) * (n + 1));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s, n);
	return (new_s);
}

/*
* It returns:
* the position of a character in a string (integer) if it exists;
* (-1) if it is not found.
*/
int	ft_findchr(const char *s, char c)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == c)
				return (i);
			i++;
		}
	}
	return (-1);
}

//It allocates the environment variables in a linked list
t_env	*ft_get_envs(char **envp)
{
	t_env	*envs;
	t_env	*new_env;
	int		i;
	int		j;

	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	envs = NULL;
	i = 0;
	while (envp[i])
	{
		j = ft_findchr(envp[i], '=');
		new_env = ft_new_env(ft_strndup(envp[i], j + 1), \
		ft_strndup(envp[j + 1], ft_strlen(envp[i])));
		if (!new_env)
		{
			ft_env_destroy(envs);
			return (NULL);
		}
		ft_env_addback(envs, new_env);
	}
	return (envs);
}
