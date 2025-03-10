/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:19 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/10 13:23:04 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 1
# define NUM_CMDS 7

# include "ast.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

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

//Uutput formatting
void	ft_output(char *str);
void	ft_output_error(char *command, char *info);

#endif
