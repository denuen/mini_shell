/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:50:19 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/25 10:00:05 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	ms_exit(t_minishell *ms)
{
	if (ms->envs)
		ft_env_destroy(ms->envs);
	if (ms->vars)
		ft_env_destroy(ms->vars);
	if (ms->ast)
		ft_ast_destroy(ms->ast);
	exit (EXIT_FAILURE);
}
