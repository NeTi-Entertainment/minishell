/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:29:20 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:21:34 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_cd_error(t_shell_data *sd, char *message, char *detail)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (detail)
	{
		ft_putstr_fd(detail, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
	sd->last_exit_status = 1;
	return (sd->last_exit_status);
}

static char	*get_cd_path(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;

	if (cmd->arg_count == 1)
	{
		path = get_env_value(shell_data->env, "HOME");
		if (!path)
			return (NULL);
	}
	else
		path = cmd->args[1];
	if (!*path)
		path = ".";
	return (path);
}

static int	check_cd_args(t_cmd *cmd, t_shell_data *shell_data)
{
	if (cmd->arg_count > 2)
		return (handle_cd_error(shell_data, "too many arguments", NULL));
	if (cmd->arg_count == 2 && \
			(cmd->args[1][0] == '-' || cmd->args[1][0] == '~'))
		return (handle_cd_error(shell_data, \
					"Only relative or absolute paths allowed", cmd->args[1]));
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;

	shell_data->last_exit_status = 0;
	if (check_cd_args(cmd, shell_data))
		return (shell_data->last_exit_status);
	path = get_cd_path(cmd, shell_data);
	if (!path)
		return (handle_cd_error(shell_data, "HOME not set", NULL));
	if (chdir(path) != 0)
		return (handle_cd_error(shell_data, strerror(errno), cmd->args[1]));
	return (shell_data->last_exit_status);
}
