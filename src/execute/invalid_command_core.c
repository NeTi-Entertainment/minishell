/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_command_core.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:52:17 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:26:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_bin_error(t_cmd *cmd, t_shell_data *shell_data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name, 2);
	ft_putendl_fd(": No such file or directory", 2);
	shell_data->last_exit_status = 127;
}

void	handle_empty_quotes_cmd(t_shell_data *shell_data)
{
	ft_putendl_fd("minishell: : command not found", 2);
	shell_data->last_exit_status = 127;
}

void	handle_special_char_cmd(t_cmd *cmd, t_shell_data *shell_data)
{
	if (cmd->name[0] == '?')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name, 2);
		ft_putendl_fd(": command not found", 2);
		shell_data->last_exit_status = 127;
	}
	if (ft_strcmp(cmd->name, "!") == 0)
		shell_data->last_exit_status = 1;
	if (ft_strcmp(cmd->name, ":") == 0)
		shell_data->last_exit_status = 0;
}

int	handle_invalid_command(t_cmd *cmd, t_shell_data *shell_data)
{
	if (!cmd || !cmd->name)
		return (0);
	if (ft_strcmp(cmd->name, "!") == 0 || ft_strcmp(cmd->name, ":") == 0 || \
			cmd->name[0] == '?')
	{
		handle_special_char_cmd(cmd, shell_data);
		return (1);
	}
	if (is_expanded_invalid_cmd(cmd->name, cmd->n_quoted, shell_data))
	{
		handle_expanded_invalid_cmd(cmd, shell_data);
		return (1);
	}
	if (ft_strcmp(cmd->name, "\"\"") == 0)
	{
		handle_empty_quotes_cmd(shell_data);
		return (1);
	}
	if (ft_strncmp(cmd->name, "/bin/", 5) == 0 && access(cmd->name, F_OK) == -1)
	{
		handle_bin_error(cmd, shell_data);
		return (1);
	}
	return (0);
}
