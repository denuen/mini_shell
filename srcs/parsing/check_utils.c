/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:33:02 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/09 16:43:58 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_iscmd(const char *s)
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

int	ms_isop(const char *s)
{
	int	len;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "||", len))
		return (1);
	else if (!ft_strncmp(s, "&&", len))
		return (1);
	else if (!ft_strncmp(s, "|", len))
		return (1);
	else if (!ft_strncmp(s, "&", len))
		return (1);
	else if (!ft_strncmp(s, "*", len))
		return (1);
	else
		return (0);
}

int	ms_isredir(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (!ft_strncmp(s, "<", len))
		return (1);
	else if (!ft_strncmp(s, ">", len))
		return (1);
	else if (!ft_strncmp(s, "<<", len))
		return (1);
	else if (!ft_strncmp(s, ">>", len))
		return (1);
	else
		return (0);
}
