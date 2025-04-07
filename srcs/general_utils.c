/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:03 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 17:55:12 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

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
	t_env	tmp;
	int		i;
	int		divisor;

	if (!envp)
		return (NULL);
	envs = NULL;
	i = 0;
	while (envp[i])
	{
		divisor = ft_findchr(envp[i], '=');
		if (divisor < 0)
			break ;
		tmp.name = ft_substr(envp[i], 0, divisor);
		tmp.value = ft_strdup(&(envp[i][divisor + 1]));
		new_env = ft_new_env(tmp.name, tmp.value);
		if (new_env)
			ft_env_addback(&envs, new_env);
		free (tmp.name);
		free (tmp.value);
		i++;
	}
	return (envs);
}

char	*ms_strnjoin(char *s1, const char *s2, int n)
{
	char	*joined;
	int		s1_len;
	int		s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n > s2_len || n == -1)
		n = s2_len;
	joined = (char *) malloc(s1_len + n + 1);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, s1_len + 1);
	ft_strlcat(joined, s2, s1_len + n + 1);
	free (s1);
	return (joined);
}
