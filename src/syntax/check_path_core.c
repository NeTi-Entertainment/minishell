/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:03:27 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 19:03:27 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_dot_command(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, ".") == 0)
		return (1);
	if (cmd[0] == '.' && cmd[1] == '.' && !cmd[2])
		return (2);
	if (cmd[0] != '/' && cmd[0] != '.')
		return (0);
	while (*cmd == '.')
		cmd++;
	if (*cmd == '\0')
		return (2);
	return (0);
}

int	is_only_path_chars(char *input)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	while (input[i])
	{
		if (input[i] != '/' && input[i] != '.' && !ft_isspace(input[i]))
			return (0);
		if (input[i] == '.')
			has_dot = 1;
		i++;
	}
	return (i > 0 && (input[0] == '/' || has_dot));
}

void	handle_dot_command(const char *cmd, t_shell_data *shell_data)
{
	int	type;

	type = is_dot_command(cmd);
	if (type == 1)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		shell_data->last_exit_status = 2;
	}
	else if (type == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell_data->last_exit_status = 127;
	}
}

int	check_directory_path(char *input)
{
	struct stat	path_stat;

	if (!is_only_path_chars(input))
		return (0);
	if (stat(input, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(input, 2);
			ft_putendl_fd(": Is a directory", 2);
			return (1);
		}
	}
	return (0);
}
