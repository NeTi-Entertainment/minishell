/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_commands_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:37:18 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 13:48:35 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* this functions in its previous version,
 * in case of error, has only 3 lines,
 * init_signals, apply redirection(cmd->redirects)
 * and execute_externals(cmd, shell_data)*/
void	execute_child_process(t_cmd *cmd, t_shell_data *shell_data)
{
	init_signals();
	if (apply_redirections(cmd->redirects))
	{
		ft_cleanup_shell(&shell_data);
		free_command(cmd);
		exit(1);
	}
	if (is_builtin(cmd->name))
	{
		g_exit_code = execute_builtin(cmd, shell_data);
		ft_cleanup_shell(&shell_data);
		free_command(cmd);
		exit(g_exit_code);
	}
	execute_external(cmd, shell_data);
	ft_cleanup_shell(&shell_data);
	free_command(cmd);
	exit(1);
}

void	handle_child_signals(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
//			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("quit: 3", STDOUT_FILENO);
	}
}

int	fork_and_execute(t_cmd *cmd, t_shell_data *shell_data)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, shell_data);
	else if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	waitpid(pid, &status, 0);
	handle_child_signals(status);
	return (status);
}
