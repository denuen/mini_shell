/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:49:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 22:25:57 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

void	ft_update_quote_state(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (c == '"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (str);
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i];
		i++;
	}
	free(str);
	return (result);
}
