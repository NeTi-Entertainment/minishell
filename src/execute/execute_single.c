/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:29:40 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 18:29:40 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_child_signals(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return ;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			g_exit_code = 131;
		}
	}
}

int	execute_builtin(t_cmd *cmd, t_shell_data *shell_data)
{
	if (cmd->prev || cmd->next)
		backup_fds(cmd->fd_info);
	if (ft_strcmp(cmd->name, "cd") == 0)
		shell_data->last_exit_status = builtin_cd(cmd, shell_data);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		shell_data->last_exit_status = builtin_echo(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		builtin_env(shell_data);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		shell_data->last_exit_status = builtin_exit(cmd, shell_data);
	else if (ft_strcmp(cmd->name, "export") == 0)
		builtin_export(cmd, shell_data);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->name, "unset") == 0)
		builtin_unset(cmd, shell_data);
	if (cmd->prev || cmd->next)
		restore_fds(cmd->fd_info, cmd);
	return (shell_data->last_exit_status);
}

void	execute_single_command(t_cmd *cmd, t_shell_data *shell_data)
{
	int		status;

	if (!cmd || !cmd->name)
		return ;
	g_exit_code = 130;
	if (is_builtin(cmd->name))
	{
		execute_builtin(cmd, shell_data);
		return ;
	}
	status = fork_and_execute(cmd, shell_data, STDIN_FILENO, NULL);
	shell_data->last_exit_status = WEXITSTATUS(status);
	g_exit_code = 0;
}

void	execute_child_process(t_cmd *cmd, t_shell_data *shell_data)
{
	int					exit_status;
	struct sigaction	sa_quit;

	sa_quit.sa_handler = SIG_DFL;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	if (is_builtin(cmd->name))
	{
		exit_status = execute_builtin(cmd, shell_data);
		ft_cleanup_shell(&shell_data);
		rl_clear_history();
		exit(exit_status);
	}
	execute_external(cmd, shell_data);
	ft_cleanup_shell(&shell_data);
	rl_clear_history();
	exit(1);
}
