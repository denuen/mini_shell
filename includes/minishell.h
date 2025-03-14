/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:19 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/14 12:52:38 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 1
# define NUM_CMDS 7

# include "ast.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

//Check
void	ms_validate_line(t_node **ast, char *line);

int		ms_validate_cmd(char **split, t_node **ast, int *i);
int		ms_validate_op(char **split, t_node **ast, int *i);
int		ms_validate_redir(char **split, t_node **ast, int *i);
//Check utils
char	*ms_isexecutable(const char *s);
char	*ms_isbuiltin(const char *s);
char	*ms_isop(const char *s);
char	*ms_isredir(const char *s);

// Output formatting
void	ft_output(char *str);
void	ft_output_error(char *command, char *info);

// executor
int		ms_executor(t_node *node);

// built ins
int		ms_cd(t_node *node);
int		ms_echo(t_node *node);
int		ms_pwd(t_node *node);

#endif
