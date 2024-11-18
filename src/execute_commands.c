/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:21:14 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 15:11:19 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_pipeline(t_cmd *cmd)
{
	return (cmd && cmd->next);
}

int	execute_builtin(t_cmd *cmd, t_shell_data *shell_data)
{
	if (cmd->prev || cmd->next)
		backup_fds(cmd->fd_info);
	if (ft_strcmp(cmd->name, "cd") == 0)
		builtin_cd(cmd, shell_data);
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
		restore_fds(cmd->fd_info);
	return (shell_data->last_exit_status);
}

void	execute_single_command(t_cmd *cmd, t_shell_data *shell_data)
{
	int		status;

	if (cmd == NULL)
	{
		ft_putendl_fd("Error: Command structure is NULL", 2);
		return ;
	}
	if (cmd->name == NULL)
		return ;
	g_exit_code = 130;
	if (is_builtin(cmd->name))
	{
		execute_builtin(cmd, shell_data);
		return ;
	}
	status = fork_and_execute(cmd, shell_data);
	shell_data->last_exit_status = WEXITSTATUS(status);
	g_exit_code = 0;
}

void	execute_commands(t_cmd *cmd, t_shell_data *shell_data)
{
	int		status;
	char	*path;

	status = 0;
	if (!cmd)
	{
		shell_data->last_exit_status = 0;
		return ;
	}
	if (check_directory_path(cmd->name))
	{
		shell_data->last_exit_status = 126;
		return ;
	}
	if (is_pipeline(cmd))
	{
		execute_pipeline(cmd, shell_data);
		return ;
	}
	if (cmd->redirects && apply_redirections(cmd->redirects))
	{
		shell_data->last_exit_status = 1;
		return ;
	}
	if (is_builtin(cmd->name))
	{
		shell_data->last_exit_status = execute_builtin(cmd, shell_data);
		return ;
	}
	else if (cmd->name)
	{
		path = find_command_path(cmd->name, shell_data->env);
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->name, 2);
			ft_putendl_fd(": command not found", 2);
			shell_data->last_exit_status = 127;
			return ;
		}
		free(path);
		status = fork_and_execute(cmd, shell_data);
		if (WIFSIGNALED(status))
			shell_data->last_exit_status = g_exit_code;
		else
			shell_data->last_exit_status = WEXITSTATUS(status);
	}
	else
		shell_data->last_exit_status = 0;
}
