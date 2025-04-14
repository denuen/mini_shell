/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:50:19 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/14 12:10:40 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <limits.h>

int	ft_isnum(char *str)
{
	int	i;

	if (str == NULL)
	{
		return (0);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (INT_MIN);
		i++;
	}
	return (1);
}

void	ms_exit(t_minishell *ms, char *status)
{
	int	exit_code;
	
	if (ft_isnum(status) == INT_MIN)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", status);
		exit_code = ms->exit_status;
	}
	else if (status == NULL)
		exit_code = sgl;
	else
		exit_code = ft_atoi(status);
	ms_destroy(ms);
	write(1, "exit\n\n", 6);
	exit (exit_code);
}
