/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:33:02 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 00:34:09 by apintaur         ###   ########.fr       */
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

int		ft_normalizepaths(char ***paths, char *line);
char	*check_direct_path(const char *s);
char	*check_path_env(const char *s);

char	*ms_isexecutable(const char *s)
{
	char	*path;

	if (!s)
		return (NULL);
	path = check_direct_path(s);
	if (path)
		return (path);
	return (check_path_env(s));
}

char	*ms_isbuiltin(const char *s)
{
	if (!s)
		return (NULL);
	if ((ft_strlen(s) == 4 && !ft_strncmp(s, "echo", 4))
		|| (ft_strlen(s) == 2 && !ft_strncmp(s, "cd", 2))
		|| (ft_strlen(s) == 3 && !ft_strncmp(s, "pwd", 3))
		|| (ft_strlen(s) == 6 && !ft_strncmp(s, "export", 6))
		|| (ft_strlen(s) == 5 && !ft_strncmp(s, "unset", 5))
		|| (ft_strlen(s) == 3 && !ft_strncmp(s, "env", 3))
		|| (ft_strlen(s) == 4 && !ft_strncmp(s, "exit", 4)))
		return ((char *)s);
	return (NULL);
}

char	*ms_isop(const char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "||", len) || !ft_strncmp(s, "&&", len) || !ft_strncmp(s,
			"|", len) || !ft_strncmp(s, "&", len))
		return ((char *)s);
	return (NULL);
}

char	*ms_isredir(const char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "<", len) || !ft_strncmp(s, ">", len) || !ft_strncmp(s,
			"<<", len) || !ft_strncmp(s, ">>", len))
		return ((char *)s);
	return (NULL);
}
