/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:19 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/09 16:40:36 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 1
# define NUM_CMDS 7

# include "ast.h"
# include <readline/readline.h>

typedef struct s_check
{
}	t_check;

typedef struct s_minishell
{
	t_node	*ast;
	t_check	checks;
}	t_minishell;

//Check utils
int	ms_iscmd(const char *s);
int	ms_isop(const char *s);
int	ms_isredir(const char *s);

//Errors msgs
int	ms_invalidcmd(const char *cmd);

#endif
