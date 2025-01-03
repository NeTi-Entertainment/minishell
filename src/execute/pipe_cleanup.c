/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:46:45 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:25:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_pipeline_fds(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->fd_info)
		{
			free(current->fd_info);
			current->fd_info = NULL;
		}
		current = current->next;
	}
}

int	create_pipe_for_cmd(t_cmd *cmd)
{
	if (!cmd->fd_info)
		fd_info_init(cmd);
	if (pipe(cmd->fd_info->pipe_fd) == -1)
		return (1);
	return (0);
}
