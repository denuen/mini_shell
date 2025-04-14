/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:50 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/25 11:45:02 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

char	*ms_get_prompt(void);

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_setter(char **prompt)
{
	struct sigaction	sa;

	*prompt = ms_get_prompt();
	sa.sa_flags = 0;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	sig_check(void)
{
	if (g_sgl != 0)
		exit(g_sgl);
}
