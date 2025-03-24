#include "../../includes/minishell.h"
#include <stdlib.h>

/*
' $ ' -> non espandibile
" $ " -> espandibile
*/

static char	*ft_expansion(t_minishell *ms, char *string, int start)
{
	t_env	*to_find;
	char	*join;
	t_env	tmp;
	int		end;

	end = start;
	while (string[end] != ' ' && string[end] != '"')
		end++;
	tmp.name = ft_substr(string, start, end - start);
	to_find = ft_env_find(ms->envs, tmp.name);
	if (!to_find)
		to_find = ft_env_find(ms->vars, tmp.name);
	if (to_find)
	{
		//Temporary string
		tmp.value = ms_strnjoin(NULL, string, start - 1);
		tmp.value = ms_strnjoin(tmp.value, to_find->value, ft_strlen(to_find->value));
		tmp.value = ms_strnjoin(tmp.value, &(string[end]), ft_strlen(string));
	}
	else
		tmp.value = ft_strdup(string);
	free (tmp.name);
	free (string);
	return (tmp.value);
}

static char	*ft_tryexpansion(t_minishell *ms, char *string)
{
	int		ret;
	int		single_q;
	int		double_q;

	ret = ft_findchr(string, "$");
	if (ret < 0)
		return (string);
	else
	{
		single_q = ft_findchr(string, '\'');
		double_q = ft_findchr(string, '"');
		if (single_q >= 0 && (double_q < 0 || (double_q > single_q)))
			return (string);
		else
			return (ft_expansion(ms, string, ret + 1));
	}
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
		split[i + j] = ft_tryexpansion(ms, split[i + j]);
		if (!split[i + j])
			return (NULL);
		j++;
	}
	new_split = (char **) malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (split[i + j])
	{
		new_split[j] = ft_strdup(split[i + j]);
		j++;
	}
	new_split[j] = NULL;
	ft_matrix_destroy(split);
	return (new_split);
}
