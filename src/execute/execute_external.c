/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:28:44 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 18:28:44 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_with_path(char *path, t_cmd *cmd, t_shell_data *sd)
{
	char	**env_array;

	env_array = env_list_to_array(sd->env);
	if (!env_array)
	{
		free(path);
		ft_cleanup_shell(&sd);
		exit(1);
	}
	if (execve(path, cmd->args, env_array) == -1)
	{
		if (errno == EACCES || errno == ENOEXEC)
		{
			free(path);
			free_env_array(env_array);
			handle_command_error(cmd, sd, 1);
		}
		free(path);
		free_env_array(env_array);
		ft_cleanup_shell(&sd);
		exit(126);
	}
}

static void	handle_ext_pid_value(pid_t pid, int wait_status, t_shell_data *sd)
{
	waitpid(pid, &wait_status, 0);
	if (WIFSIGNALED(wait_status))
	{
		if (WTERMSIG(wait_status) == SIGQUIT)
		{
			ft_putendl_fd("Quit (core dumped)", 2);
			sd->last_exit_status = WTERMSIG(wait_status) + 128;
		}
	}
	else
		sd->last_exit_status = WEXITSTATUS(wait_status);
}

void	handle_external_command(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;
	pid_t	pid;
	int		wait_status;

	wait_status = 0;
	path = find_command_path(cmd->name, shell_data->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name, 2);
		if (cmd->name[0] == '.' || cmd->name[0] == '/')
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(": command not found", 2);
		shell_data->last_exit_status = 127;
		return ;
	}
	free(path);
	pid = fork_and_execute(cmd, shell_data, STDIN_FILENO, NULL);
	if (pid > 0)
		handle_ext_pid_value(pid, wait_status, shell_data);
}

void	execute_external(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;

	check_redirect_arg_error(cmd->args, shell_data);
	path = find_command_path(cmd->name, shell_data->env);
	if (!path)
		handle_command_error(cmd, shell_data, 0);
	check_file_permissions(path, cmd, shell_data);
	execute_with_path(path, cmd, shell_data);
	free(path);
}
