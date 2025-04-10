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

void sig_handler(int sig, siginfo_t *info, void *void_ms)
{
	t_minishell *ms;

	if (sig == SIGINT)
	{
		ft_printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		sgl = 1;
	}
	(void)info;
	ms = (t_minishell *)void_ms;
	(void)ms;
}

int signal_receiver(t_minishell *ms)
{
	struct sigaction sa;
	(void)ms;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error registering SIGINT handler");
		return -1;
	}
	return 0;
}

void sig_check(void)
{
	if (sgl == 1)
		exit(1);
}
