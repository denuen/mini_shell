/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:06:56 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/04 14:57:32 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//da sistemare per display solo sullo standard error per il cambio dell'STDOUT
void	ft_output_error(char *command, char *info)
{
		rl_on_new_line();
		ft_printf("%s: %s: %s", command, strerror(errno), info);
		rl_on_new_line();
		rl_redisplay();
}

void	ft_output(char *str)
{
		rl_on_new_line();
		rl_replace_line(str, 0);
		rl_redisplay();
		rl_on_new_line();
}
