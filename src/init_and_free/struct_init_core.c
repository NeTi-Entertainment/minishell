/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:27:46 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:28:38 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->n_quoted = 0;
	cmd->redirects = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_info = NULL;
	cmd->tty_backup = -1;
	cmd->has_heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->has_next = 0;
	cmd->quoted = 0;
	cmd->arg_quoted = NULL;
	return (cmd);
}

void	fd_info_init(t_cmd *cmd)
{
	if (!cmd->fd_info)
	{
		cmd->fd_info = malloc(sizeof(t_fd_info));
		if (!cmd->fd_info)
			return ;
	}
	cmd->fd_info->stdin_backup = -1;
	cmd->fd_info->stdout_backup = -1;
	cmd->fd_info->pipe_fd[0] = -1;
	cmd->fd_info->pipe_fd[1] = -1;
}
