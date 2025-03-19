/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:40:43 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/19 16:58:21 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	ms_counter(char s, char *open, size_t *cnt)
{
	if (s == '\0')
	// funzione per aspettare l'unquote
	if ((s == '"' || s == '\'') && *open == '\0')
	{
		*open = s;
	}
	else if (s == *open && *open != '\0')
	{
		*open = '\0';
	}
	(*cnt)++;
}

char	**ms_misery_init(size_t *i, size_t* k, const char* s, char c)
{
	*i = 0;
	*k = 0;
	return (ms_ssalloc(s, c));
}

void	ms_split_checks(char s, char *open, int *i)
{
	if (s == '\0')
		// funzione per aspettare l'unquote
	if ((s == '"' || s == '\'') && *open == '\0')
	{
		*open = s;
	}
	else if (s == *open && *open != '\0')
	{
		*open = '\0';
	}
	(*i)++;
}