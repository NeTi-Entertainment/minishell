/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:06:41 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:25:28 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redirect_arg_error(char **args, t_shell_data *shell_data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>')
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": No such file or directory", 2);
			shell_data->last_exit_status = 2;
			exit (1);
		}
		i++;
	}
	return (shell_data->last_exit_status);
}

void	handle_command_error(t_cmd *cmd, t_shell_data *sd, int is_permission)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name, 2);
	if (is_permission)
	{
		ft_putendl_fd(": Permission denied", 2);
		ft_cleanup_shell(&sd);
		exit(126);
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		ft_cleanup_shell(&sd);
		exit(127);
	}
}

void	check_file_permissions(char *path, t_cmd *cmd, t_shell_data *sd)
{
	struct stat	path_stat;

	if (cmd->name[0] == '.' && cmd->name[1] == '/')
	{
		if (stat(cmd->name, &path_stat) == 0)
		{
			if (!S_ISREG(path_stat.st_mode) || access(cmd->name, X_OK) != 0)
			{
				free(path);
				handle_command_error(cmd, sd, 1);
			}
		}
	}
}
