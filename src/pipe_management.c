/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:11 by caubert           #+#    #+#             */
/*   Updated: 2024/11/11 14:31:11 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipe_for_cmd(t_cmd *cmd)
{
	if (!cmd->fd_info)
		fd_info_init(cmd);
	if (pipe(cmd->fd_info->pipe_fd) == -1)
		return (1);
	return (0);
}

void	fork_and_execute_pipe(t_cmd *cmd, int i_fd, int *p_fd, t_shell_data *sd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (i_fd != STDIN_FILENO)
		{
			dup2(i_fd, STDIN_FILENO);
			close(i_fd);
		}
		if (p_fd && p_fd[1] != STDOUT_FILENO)
		{
			dup2(p_fd[1], STDOUT_FILENO);
			close(p_fd[1]);
		}
		if (p_fd)
			close(p_fd[0]);
		execute_child_process(cmd, sd);
	}
	if (i_fd != STDIN_FILENO)
		close(i_fd);
	if (p_fd && p_fd[1] != STDIN_FILENO)
		close(p_fd[1]);
}

void	execute_pipeline(t_cmd *cmd, t_shell_data *shell_data)
{
	t_cmd	*current;
	int		input_fd;
	int		*pipe_fds;
	int		status;

	create_all_pipes(cmd);
	current = cmd;
	input_fd = STDIN_FILENO;
	backup_fds(current->fd_info);
	while (current)
	{
		if (current->next)
			pipe_fds = current->fd_info->pipe_fd;
		else
			pipe_fds = NULL;
		fork_and_execute_pipe(current, input_fd, pipe_fds, shell_data);
		if (pipe_fds)
			input_fd = pipe_fds[0];
		current = current->next;
	}
	restore_fds(cmd->fd_info);
	cleanup_all_pipes(cmd);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	current = cmd; //ajout a partir de cette ligne -- en faire une fonction de clean
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
