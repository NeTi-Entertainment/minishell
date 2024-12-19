/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:47:11 by caubert           #+#    #+#             */
/*   Updated: 2024/12/15 20:47:11 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_heredoc_line(char *line, t_shell_data *shell)
{
	char	*expanded;
	char	*temp;
	size_t	len;

	if (!line || !*line)
		return (NULL);
	temp = expand_variables(line, shell);
	free(line);
	if (!temp)
		return (ft_strdup(""));
	len = ft_strlen(temp);
	if (len >= 2 && temp[0] == '"' && temp[len - 1] == '"')
	{
		expanded = ft_strndup(temp + 1, len - 2);
		free(temp);
		return (expanded);
	}
	return (temp);
}

static void	process_heredoc_line(char *line, int fd_write, int exp)
{
	char	*expanded_line;

	if (exp)
		expanded_line = expand_heredoc_line(line, get_shell_data());
	else
		expanded_line = line;
	if (expanded_line)
	{
		write(fd_write, expanded_line, ft_strlen(expanded_line));
		write(fd_write, "\n", 1);
		free(expanded_line);
	}
}

int	read_minimal_heredoc(int fd_write, const char *delimiter, int exp)
{
	char	*line;
	char	*clean_delim;
	int		ret;

	ret = 0;
	clean_delim = clean_delimiter(delimiter);
	if (!clean_delim)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			return (0);
		}
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, fd_write, exp);
	}
	free(clean_delim);
	return (ret);
}
