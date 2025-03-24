/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:50 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/24 13:12:09 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_check(void)
{
	if (signal == 1)
		exit(1);
}

//la funzione di signal handling va inserita nella funzione d'esecuzione madre, quella che creerà
// un processo apposito per lo svolgimento dell'albero binario