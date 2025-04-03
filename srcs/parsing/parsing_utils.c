/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:33:02 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/03 14:40:37 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

/*

access flags

F_OK → Check if the file exists.
R_OK → Check if it's readable.
W_OK → Check if it's writable.
X_OK → Check if it's executable.

*/

static int	ft_normalizepaths(char ***paths, char *line);

char	*ms_isexecutable(const char *s)
{
	int		i;
	char	**paths;
	char	*string;
	char	*normalized_path;

	string = getenv("PATH");
	if (!string || !s)
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

char	*ms_isbuiltin(const char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "echo", len) || !ft_strncmp(s, "cd", len)
		|| !ft_strncmp(s, "pwd", len) || !ft_strncmp(s, "export", len)
		|| !ft_strncmp(s, "unset", len) || !ft_strncmp(s, "env", len)
		|| !ft_strncmp(s, "exit", len))
		return ((char*)s);
	return (NULL);
}

char	*ms_isop(const char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "||", len) || !ft_strncmp(s, "&&", len)
		|| !ft_strncmp(s, "|", len) || !ft_strncmp(s, "&", len)
		|| !ft_strncmp(s, "*", len))
		return ((char*)s);
	return (NULL);
}

char	*ms_isredir(const char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "<", len) || !ft_strncmp(s, ">", len)
		|| !ft_strncmp(s, "<<", len) || !ft_strncmp(s, ">>", len))
		return ((char*)s);
	return (NULL);
}

static int	ft_normalizepaths(char ***paths, char *line)
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
