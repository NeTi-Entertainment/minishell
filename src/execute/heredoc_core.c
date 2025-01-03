/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:46:02 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:25:40 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_temp_file(void)
{
	static int	count;
	char		*name;
	char		*num;
	char		*temp;

	count = 0;
	num = ft_itoa(count++);
	if (!num)
		return (NULL);
	temp = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	name = ft_strdup(temp);
	free(temp);
	return (name);
}

static int	write_heredoc_content(int fd, char *delimiter, int expand, \
				t_shell_data *sd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (expand)
			line = expand_variables(line, sd);
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

static int	create_and_write_heredoc(char *del, int eof_quoted, char **temp, \
				t_shell_data *sd)
{
	int	fd;

	*temp = create_temp_file();
	if (!*temp)
		return (-1);
	fd = open(*temp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(*temp);
		return (-1);
	}
	if (write_heredoc_content(fd, del, !eof_quoted, sd) == -1)
	{
		close(fd);
		unlink(*temp);
		free(*temp);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(char *delimiter, int eof_quoted, t_shell_data *sd)
{
	char	*temp_file;
	int		read_fd;
	int		ret;

	ret = create_and_write_heredoc(delimiter, eof_quoted, &temp_file, sd);
	if (ret == -1)
		return (-1);
	read_fd = open(temp_file, O_RDONLY);
	unlink(temp_file);
	free(temp_file);
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		return (-1);
	}
	return (0);
}
