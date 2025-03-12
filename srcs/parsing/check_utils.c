/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:33:02 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/13 00:19:05 by apintaur         ###   ########.fr       */
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

static int	ft_normalizepath(char ***paths, char *line);
void		*ft_ssdestroy(char **ss);

char	*ms_isexecutable(const char *s)
{
	int		i;
	char	**paths;
	char	*string;

	string = getenv("PATH");
	if (!string)
		return (0);
	i = 0;
	string = NULL;
	paths = ft_split(string, ':');
	ft_normalizepath(&paths, s);
	while (paths[i])
	{
		if (!access(paths[i], F_OK | W_OK | X_OK))
		{
			string = ft_strdup(paths[i]);
			break ;
		}
		i++;
	}
	ft_ssdestroy(paths);
	return (string);
}

int	ms_isbuiltin(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "echo", len))
		return (1);
	else if (!ft_strncmp(s, "cd", len))
		return (1);
	else if (!ft_strncmp(s, "pwd", len))
		return (1);
	else if (!ft_strncmp(s, "export", len))
		return (1);
	else if (!ft_strncmp(s, "unset", len))
		return (1);
	else if (!ft_strncmp(s, "env", len))
		return (1);
	else if (!ft_strncmp(s, "exit", len))
		return (1);
	else
		return (0);
}

char	*ms_isop(const char *s)
{
	int	len;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "||", len) || !ft_strncmp(s, "&&", len)
		|| !ft_strncmp(s, "|", len) || !ft_strncmp(s, "&", len)
		|| !ft_strncmp(s, "*", len))
		return (s);
	else
		return (NULL);
}

char	*ms_isredir(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "<", len) || !ft_strncmp(s, ">", len)
		|| !ft_strncmp(s, "<<", len) || !ft_strncmp(s, ">>", len))
		return (s);
	else
		return (NULL);
}

static int	ft_normalizepath(char ***paths, char *line)
{
	int		i;
	char	*tmp;

	if (!paths || !(*paths) || !line)
		return (0);
	i = 0;
	while ((*paths)[i])
	{
		tmp = ft_strjoin((*paths)[i], line);
		free ((*paths)[i]);
		(*paths)[i] = tmp;
		i++;
	}
	return (1);
}
