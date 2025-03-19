#include "../../includes/minishell.h"
#include <stdlib.h>

/*
' $ ' -> non espandibile
" $ " -> espandibile
*/

int	ft_quote_case(char **split, int i, char type)
{
	int	pos;

	pos = ft_findchr(split[i], type);
	if (pos > 0 && ft_findchr(&(split[i][pos + 1]), type) > 0)
		return (1);
	else if (pos > 0)
		return (-1);
	return (0);
}

static char	*ft_expand_var(t_minishell *ms, char **split, int i)
{
	char	*new_string;
	t_env	*var;
	char	*var_name;
	int		var_len;
	int		j;

	j = ft_findchr(split[i], '$') + 1;
	var_len = ft_strlen(&(split[i][j]));
	var_name = (char *) malloc(sizeof(char *) * (var_len + 1));
	ft_strlcpy(var_name, split[i], var_len);
	j = ft_findchr(var_name, '\"');
	if (j > 0)
		var_name[j] = '\0';
	var = ft_env_find(ms->envs, var_name);
	if (var != NULL)
		new_string = ft_strdup(var->value);
	else
	{
		var = ft_env_find(ms->vars, var_name);
		if (!var)
			new_string = NULL;
		else
			new_string = ft_strdup(var->value);
	}
	free (split[i]);
	free (var_name);
	return (new_string);
}

static char	*ft_tryexpansion(t_minishell *ms, char **split, int i)
{
	int	ret;

	if (ft_findchr(split[i], '$'))
	{
		ret = ft_quote_case(split, i, '\'');
		if (ret < 0)
			return (ft_handle_openquote(ms, split, i, "\'"));
		else if (ret > 0)
			return (split[i]);
		else if (!ret)
		{
			ret = ft_quote_case(split, i, '\"');
			if (ret > 0 || ret == 0)
				return (ft_expand_var(ms, split, i));
			else if (ret < 0)
			{
				return (ft_handle_openquote(ms, split, i, '\"'));
				return (NULL);
			}
		}
	}
	return (split[i]);
}

char	**ft_rearrange_line(t_minishell *ms, char **split)
{
	char	**new_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (split[i] && ft_findchr(split[i], '=') > 0)
		i++;
	while (split[i + j])
	{
		split[i + j] = ft_tryexpansion(ms, split, (i + j));
		if (!split)
			return (NULL);
		j++;
	}
}
