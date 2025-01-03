/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:21 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:27:04 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_piped_commands(t_cmd *cmd, t_shell_data *sd)
{
	t_cmd		*current;
	int			input_fd;
	int			*pipe_fds;

	current = cmd;
	input_fd = STDIN_FILENO;
	if (current->has_heredoc && current->tty_backup != -1)
		input_fd = cmd->heredoc_fd;
	while (current)
	{
		pipe_fds = NULL;
		current->has_next = (current->next != NULL);
		if (current->has_next)
			pipe_fds = current->fd_info->pipe_fd;
		current->pid = fork_and_execute(current, sd, input_fd, pipe_fds);
		if (pipe_fds)
			input_fd = pipe_fds[0];
		current = current->next;
	}
}

void	handle_pid_value(pid_t wpid, int status, t_shell_data *sd, t_cmd *cmd)
{
	if (wpid == cmd->pid)
	{
		if (WIFEXITED(status))
			sd->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sd->last_exit_status = WTERMSIG(status) + 128;
			if (WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd("Quit (core dumped)", 2);
		}
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
}

void	wait_for_children(t_shell_data *shell_data, int child_count)
{
	int		status;
	int		i;
	pid_t	wpid;
	t_cmd	*last_cmd;

	i = 0;
	last_cmd = shell_data->cmd;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	while (i < child_count)
	{
		status = 0;
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
			break ;
		handle_pid_value(wpid, status, shell_data, last_cmd);
		i++;
	}
}

void	execute_pipeline(t_cmd *cmd, t_shell_data *shell_data)
{
	int		child_count;
	t_cmd	*current;

	child_count = 0;
	current = cmd;
	while (current)
	{
		child_count++;
		current = current->next;
	}
	create_all_pipes(cmd);
	backup_fds(cmd->fd_info);
	execute_piped_commands(cmd, shell_data);
	restore_fds(cmd->fd_info, cmd);
	cleanup_all_pipes(cmd);
	wait_for_children(shell_data, child_count);
	cleanup_pipeline_fds(cmd);
	if (cmd->tty_backup != -1)
	{
		dup2(cmd->tty_backup, STDIN_FILENO);
		close(cmd->tty_backup);
		cmd->tty_backup = -1;
	}
}
