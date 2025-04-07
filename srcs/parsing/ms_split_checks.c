/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:49:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 13:34:32 by apintaur         ###   ########.fr       */
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

char	*ft_remove_quotes(char *result, char quote)
{
	char	*clean_result;
	int		i;

	i = ft_findchr(result, quote);
	if (i > 0)
	{
		clean_result = ft_substr(result, 0, i);
		ft_printf("%s\n", clean_result);
		clean_result = ms_strnjoin(clean_result, &(result[i + 1]), \
		ft_findchr(&(result[i + 1]), quote));
		free(result);
		return (clean_result);
	}
	else
		return (result);
}
