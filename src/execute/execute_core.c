/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:28:29 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:26:24 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_home_directory(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;

	shell_data->last_exit_status = 0;
	path = get_env_value(shell_data->env, "HOME");
	if (path && ft_strcmp(cmd->name, path) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name, 2);
		ft_putendl_fd(": Is a directory", 2);
		shell_data->last_exit_status = 126;
		return ;
	}
}

int	handle_special_cases(t_cmd *cmd, t_shell_data *shell_data)
{
	handle_home_directory(cmd, shell_data);
	if (shell_data->last_exit_status == 126)
		return (1);
	if (is_dot_command(cmd->name))
	{
		handle_dot_command(cmd->name, shell_data);
		return (1);
	}
	if (check_directory_path(cmd->name))
	{
		shell_data->last_exit_status = 126;
		return (1);
	}
	return (0);
}

static void	handle_command_execution(t_cmd *cmd, t_shell_data *sd)
{
	if (is_pipeline(cmd))
	{
		execute_pipeline(cmd, sd);
		if (cmd->fd_info)
			restore_fds(cmd->fd_info, cmd);
		return ;
	}
	if (is_builtin(cmd->name))
	{
		sd->last_exit_status = execute_builtin(cmd, sd);
		if (cmd->fd_info)
			restore_fds(cmd->fd_info, cmd);
		return ;
	}
	else if (cmd->name)
	{
		handle_external_command(cmd, sd);
		if (cmd->fd_info)
			restore_fds(cmd->fd_info, cmd);
	}
	else
		sd->last_exit_status = 0;
}

static int	handle_redirections(t_cmd *cmd, t_shell_data *shell_data)
{
	if (cmd->redirects && apply_redirections(cmd->redirects, shell_data))
	{
		shell_data->last_exit_status = 1;
		return (1);
	}
	return (0);
}

void	execute_commands(t_cmd *cmd, t_shell_data *shell_data)
{
	if (!cmd || !shell_data || handle_invalid_command(cmd, shell_data) || \
			handle_special_cases(cmd, shell_data))
		return ;
	fd_info_init(cmd);
	if (!cmd->fd_info)
		return ;
	backup_fds(cmd->fd_info);
	if (!is_pipeline(cmd) && handle_redirections(cmd, shell_data))
	{
		restore_fds(cmd->fd_info, cmd);
		return ;
	}
	handle_command_execution(cmd, shell_data);
	if (cmd->fd_info)
		restore_fds(cmd->fd_info, cmd);
}
