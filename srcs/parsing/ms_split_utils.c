/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:45:41 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/07 10:30:05 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

void	ft_wait_for_quotes(char **line, char end);
void	ft_wait_for_eof(char **line, int start);
char	*ft_process_heredoc(char *new_line, char *eoff);
char	*ft_remove_quotes(char *result, char quote);

void	ft_check_for_redir(char **line)
{
	char	*s;
	int		i;
	int		start;

	s = *line;
	i = ft_findchr(s, '<');
	if (i > 0 && s[i + 1] == '<')
		start = i;
	else
		start = -1;
	if (start >= 0)
		ft_wait_for_eof(line, start + 2);
}

void	ft_check_for_quotes(char **line)
{
	char	*s;
	int		i;
	char	end;

	s = *line;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			end = s[i];
			i++;
			while (s[i] && s[i] != end)
				i++;
			if (!s[i])
				ft_wait_for_quotes(line, end);
			else
				i++;
		}
		i++;
	}
}

void	ft_wait_for_quotes(char **line, char end)
{
	char	*s;
	char	*result;
	char	*new_line;
	int		i;

	s = *line;
	result = ft_strdup(s);
	i = -1;
	while (i < 0)
	{
		new_line = readline("quote> ");
		if (!new_line)
			break ;
		i = ft_findchr(new_line, end);
		result = ms_strnjoin(result, new_line, ft_strlen(new_line));
		free(new_line);
		if (i > 0)
			break ;
	}
	*line = ft_remove_quotes(result, end);
}

void	ft_wait_for_eof(char **line, int start)
{
	char	*s;
	int		end;
	char	*eoff;
	char	*new_line;

	s = *line;
	while ((s[start] >= 9 && s[start] <= 13) || s[start] == 32)
		start++;
	new_line = ft_substr(s, 0, start - 3);
	end = start;
	while (s[end] && !((s[end] >= 9 && s[end] <= 13) || s[end] == 32))
		end++;
	eoff = ft_substr(s, start, end - start);
	new_line = ft_process_heredoc(new_line, eoff);
	new_line = ms_strnjoin(new_line, &(s[end]), -1);
	free(s);
	*line = new_line;
}

char	*ft_process_heredoc(char *new_line, char *eoff)
{
	char	*read;

	while (1)
	{
		read = readline("heredoc> ");
		if (!read)
			break ;
		if (ft_strnstr(read, eoff, ft_strlen(new_line) + 1))
		{
			new_line = ms_strnjoin(new_line, read, \
				ft_strlen(read) - ft_strlen(eoff));
			free(read);
			break ;
		}
		new_line = ms_strnjoin(new_line, read, -1);
		new_line = ms_strnjoin(new_line, " ", 1);
		free(read);
	}
	free(eoff);
	return (new_line);
}
