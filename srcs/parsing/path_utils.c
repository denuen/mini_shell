/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:09:48 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 00:33:46 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_normalizepaths(char ***paths, char *line)
{
	int		i;
	char	*tmp;
	char	*n_path;

	if (!paths || !(*paths) || !line)
		return (0);
	i = 0;
	while ((*paths)[i])
	{
		n_path = ft_strjoin((*paths)[i], "/");
		if (!n_path)
			return (0);
		tmp = ft_strjoin(n_path, line);
		free(n_path);
		free((*paths)[i]);
		(*paths)[i] = tmp;
		i++;
	}
	return (1);
}

char	*check_path_env(const char *s)
{
	int		i;
	char	**paths;
	char	*string;
	char	*normalized_path;

	string = getenv("PATH");
	if (!string)
		return (NULL);
	i = 0;
	normalized_path = NULL;
	paths = ft_split(string, ':');
	if (!paths)
		return (NULL);
	ft_normalizepaths(&paths, (char *)s);
	while (paths[i])
	{
		if (!access(paths[i], F_OK | X_OK))
		{
			normalized_path = ft_strdup(paths[i]);
			break ;
		}
		i++;
	}
	ft_matrix_destroy((void **)paths);
	return (normalized_path);
}

char	*check_direct_path(const char *s)
{
	if (ft_strchr(s, '/'))
	{
		if (!access(s, F_OK | X_OK))
			return (ft_strdup(s));
		return (NULL);
	}
	return (NULL);
}
