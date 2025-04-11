/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:19 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/11 10:08:33 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 1
# define NUM_CMDS 7
# define SINGLE 0
# define DOUBLE 1

# include "ast.h"
# include "env.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_utils
{
	int	i;
	int	j;
	int	squote;
	int	dquote;
}	t_utils;

typedef struct s_minishell
{
	t_node	*ast;
	t_env	*envs;
	t_env	*vars;
	int		exit_status;
}	t_minishell;

extern char	**environ;
extern int	sgl;

// Check
void	ms_validate_line(t_minishell *ms, char *line);

int		ms_validate_cmd(t_minishell *ms, char **split, int *i);
int		ms_validate_op(t_minishell *ms, char **split, int *i);
int		ms_validate_redir(t_minishell *ms, char **split, int *i);

// Check utils
char	*ms_isexecutable(const char *s);
char	*ms_isbuiltin(const char *s);
char	*ms_isop(const char *s);
char	*ms_isredir(const char *s);

// Parsing errors
int		ft_matrix_destroy(void **ptr);
void	ft_input_error(char **split, int i);

// Output formatting
void	ft_output(char *str);
void	ft_output_error(char *command, char *info);

// executor
int		ms_executor(t_node *node, t_minishell *ms);

// built ins
int		ms_cd(t_node *node);
int		ms_echo(t_node *node);
int		ms_export(t_node *node, t_minishell *ms);
int		ms_pwd(t_node *node);
int		ms_unset(t_node *node, t_minishell *ms);
int		ms_exit(t_minishell *ms);
int		ms_env(t_env *envs);

// General utils
int		ft_findchr(const char *s, char c);
char	*ms_strnjoin(char *s1, const char *s2, int n);
t_env	*ft_get_envs(void);
char	**ms_split(char *s, char c, t_minishell *ms);
void	ms_destroy(t_minishell *ms);

// signals
void	sig_check(void);
int		sgl_moving(t_minishell *ms);
int		sgl_still(t_minishell *ms);

#endif
