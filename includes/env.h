/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:49:53 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/24 23:10:55 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
} t_env;

t_env	*ft_new_env(char *name, char *value);
void	ft_env_destroy(t_env *envs);

void	ft_env_addordered(t_env **envs, t_env *new_env);
void	ft_env_addback(t_env **envs, t_env *new_env);
t_env	*ft_env_find(t_env *envs, char *name);
void 	ft_env_remove(t_env **envs, char *name);
void	ft_env_print(t_env *envs);

#endif
