/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:06:56 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/10 16:14:48 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_output_error(char *command, char *info)
{
		rl_on_new_line();
		printf("%s: %s: %s", command, strerror(errno), info);
		rl_on_new_line();
		rl_redisplay();
}

void	ft_output(char *str)
{
		rl_on_new_line();
		rl_replace_line(str, 0);
		rl_redisplay();
		rl_on_new_line();
		rl_redisplay();
}