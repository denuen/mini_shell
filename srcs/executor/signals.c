/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:50 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/25 11:45:02 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int sig, siginfo_t *info, void *void_ms)
{
	t_minishell	*ms;

	if (sig == SIGINT)
	{
		signal = 1;
		ft_putstr_fd("\n", 1);
	}
	(void)info;
	ms = (t_minishell *)void_ms;
}

int	signal_receiver(t_minishell *ms)
{
	struct sigaction	sa;

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

void	sig_check(void)
{
	if (signal == 1)
		exit(1);
}

//la funzione di signal handling va inserita nella funzione d'esecuzione madre, quella che creerà
// un processo apposito per lo svolgimento dell'albero binario