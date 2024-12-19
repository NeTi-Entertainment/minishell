/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:34 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 18:30:34 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	backup_fds(t_fd_info *fd_info)
{
	fd_info->stdin_backup = dup(STDIN_FILENO);
	fd_info->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_fds(t_fd_info *fd_info, t_cmd *cmd)
{
	if (!cmd->has_heredoc && fd_info->stdin_backup != -1)
	{
		dup2(fd_info->stdin_backup, STDIN_FILENO);
		close(fd_info->stdin_backup);
	}
	if (fd_info->stdout_backup != -1)
	{
		dup2(fd_info->stdout_backup, STDOUT_FILENO);
		close(fd_info->stdout_backup);
	}
}

void	create_all_pipes(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd && cmd->next)
	{
		fd_info_init(cmd);
		create_pipe_for_cmd(cmd);
		cmd = cmd->next;
	}
	if (cmd)
		fd_info_init(cmd);
}

void	cleanup_pipe(t_fd_info *fd_info)
{
	if (fd_info->pipe_fd[0] != -1)
		close(fd_info->pipe_fd[0]);
	if (fd_info->pipe_fd[1] != -1)
		close(fd_info->pipe_fd[1]);
	fd_info->pipe_fd[0] = -1;
	fd_info->pipe_fd[1] = -1;
}

void	cleanup_all_pipes(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->fd_info)
			cleanup_pipe(current->fd_info);
		current = current->next;
	}
}
