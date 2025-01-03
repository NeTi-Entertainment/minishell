/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:01 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:24:36 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pipe_fds(int *pipe_fd)
{
	if (!pipe_fd)
		return ;
	if (pipe_fd[1] != STDOUT_FILENO)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
}

void	handle_input_fd(int input_fd)
{
	if (input_fd == STDIN_FILENO)
		return ;
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit(1);
	close(input_fd);
}

int	fork_and_execute(t_cmd *cmd, t_shell_data *sd, int input_fd, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		handle_pipe_fds(pipe_fd);
		handle_input_fd(input_fd);
		execute_child_process(cmd, sd);
	}
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (!pipe_fd && WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (pipe_fd && pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (pid);
}
