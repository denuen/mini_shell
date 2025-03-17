/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:08 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/17 14:49:30 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

//Lower number -> highest priority
# define COMMAND 0
# define OPERATOR 1
# define REDIRECTION 2

# include "libft/includes/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	int				type;
	char			**cmd;
	char			*op;
	char			**redir;
	int				priority;
	t_env			*env;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

// Ast memory management
t_node	*ft_ast_newcommand(char **cmd);
t_node	*ft_ast_newop(char *op);
t_node	*ft_ast_newredir(char *redir);
void	ft_ast_destroy(t_node *node);

// Ast operations
t_node	*ft_ast_insertnode(t_node *ast, t_node *new_node);
void	ft_ast_addleft(t_node *ast, t_node *node);
void	ft_ast_addright(t_node *ast, t_node *node);

// Debugging functions
void	ft_ast_printtree(t_node *node);
void	ft_ast_printcmd(t_node *node);
int		ft_ast_size(t_node *node);
#endif
