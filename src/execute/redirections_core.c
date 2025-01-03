/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:58:38 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:27:13 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_file(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (-1);
	}
	return (fd);
}

static int	handle_input_redirect(char *file)
{
	int	fd;

	fd = open_file(file, O_RDONLY, 0);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redirect(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open_file(file, flags, 0644);
	if (fd == -1)
		return (1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	return (close(fd));
}

int	apply_redirections(t_redirect *redirects, t_shell_data *sd)
{
	t_redirect	*current;
	int			ret;

	current = redirects;
	while (current)
	{
		if (current->type == 0)
			ret = handle_input_redirect(current->file);
		else if (current->type == 1)
			ret = handle_output_redirect(current->file, 0);
		else if (current->type == 2)
		{
			ret = handle_heredoc(current->file, current->eof_quoted, sd);
			if (ret == -1)
				return (1);
		}
		else if (current->type == 3)
			ret = handle_output_redirect(current->file, 1);
		if (ret != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
