/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:22:36 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 14:34:34 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_file(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	return (fd);
}

static int	handle_input_redirect(char *file)
{
	int	fd;

	fd = open_file(file, O_RDONLY, 0);
	if (fd == -1)
	{
		g_exit_code = 1;
		return (g_exit_code);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (g_exit_code);
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
	{
		g_exit_code = 1;
		return (g_exit_code);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (g_exit_code);
}

int	apply_redirections(t_redirect *redirects)
{
	t_redirect	*current;
	int			ret;

	current = redirects;
	g_exit_code = 0;
	while (current)
	{
		if (current->type == 0)
			ret = handle_input_redirect(current->file);
		else if (current->type == 1)
			ret = handle_output_redirect(current->file, 0);
		else if (current->type == 3)
			ret = handle_output_redirect(current->file, 1);
		if (ret != 0)
		{
			g_exit_code = 1;
			return (g_exit_code);
		}
		current = current->next;
	}
	return (g_exit_code);
}
