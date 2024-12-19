/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:32:43 by caubert           #+#    #+#             */
/*   Updated: 2024/12/15 20:32:43 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	setup_heredoc_input(int read_fd)
{
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		return (-1);
	}
	close(read_fd);
	return (0);
}

int	cleanup_heredoc_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
	return (-1);
}

int	validate_delimiter(const char *delimiter)
{
	if (!delimiter || !*delimiter)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("syntax error near unexpected token 'newline'", 2);
		return (0);
	}
	return (1);
}

char	*clean_delimiter(const char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (len < 3)
		return (ft_strdup(delimiter));
	if (delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		return (ft_strndup(delimiter + 1, len - 2));
	if (delimiter[0] == '"' && delimiter[len - 1] == '"')
		return (ft_strndup(delimiter + 1, len - 2));
	return (ft_strdup(delimiter));
}

void	cleanup_heredoc_process(void)
{
	t_shell_data	*shell;

	shell = get_shell_data();
	if (shell->cmd)
	{
		free_command(shell->cmd);
		shell->cmd = NULL;
	}
	ft_cleanup_env(&shell->env);
	free(shell);
}
