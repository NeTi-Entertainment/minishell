/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:21:33 by caubert           #+#    #+#             */
/*   Updated: 2024/10/16 12:54:02 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_redirect_arg_error(char **args)
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
			g_exit_code = 2;
			exit (1);
		}
		i++;
	}
	return (g_exit_code);
}

void	execute_external(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;
	char	**env_array;

	check_redirect_arg_error(cmd->args);
	path = find_command_path(cmd->name, shell_data->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name, 2);
		ft_putendl_fd(": command not found", 2);
		ft_cleanup_shell(&shell_data);
		free_command(cmd);
		exit(127);
	}
	env_array = env_list_to_array(shell_data->env);
	if (!env_array)
	{
		free(path);
		ft_cleanup_shell(&shell_data);
		free_command(cmd);
		exit(1);
	}
	if (execve(path, cmd->args, env_array) == -1)
	{
		if (errno != ENOENT)
			perror("minishell: ");
		free(path);
		free_env_array(env_array);
		ft_cleanup_shell(&shell_data);
		free_command(cmd);
		exit(126);
	}
	free(path);
	free_env_array(env_array);
}

int	is_builtin(char *cmd_name)
{
	return (ft_strcmp(cmd_name, "cd") == 0 || \
		ft_strcmp(cmd_name, "echo") == 0 || \
		ft_strcmp(cmd_name, "env") == 0 || \
		ft_strcmp(cmd_name, "exit") == 0 || \
		ft_strcmp(cmd_name, "export") == 0 || \
		ft_strcmp(cmd_name, "pwd") == 0 || \
		ft_strcmp(cmd_name, "unset") == 0);
}

char	*join_path(const char *dir, const char *file)
{
	char	*path;
	char	*tmp;

	if (!dir || !file)
		return (NULL);
	path = ft_strdup(dir);
	if (!path)
		return (NULL);
	tmp = path;
	path = ft_strjoin(path, "/");
	free(tmp);
	if (!path)
		return (NULL);
	tmp = path;
	path = ft_strjoin(tmp, file);
	free(tmp);
	return (path);
}

char	*find_command_path(const char *cmd, t_env *env)
{
	char	*path_env;
	char	*full_path;
	char	*dir_start;
	char	*dir_end;
	char	*dir;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	dir_start = path_env;
	while (*dir_start)
	{
		while (*dir_start == ':')
			dir_start++;
		dir_end = ft_strchr(dir_start, ':');
		if (!dir_end)
		{
			dir = ft_strdup(dir_start);
			if (!dir)
				return (NULL);
			full_path = join_path(dir, cmd);
			free(dir);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			break ;
		}
		dir = ft_strndup(dir_start, dir_end - dir_start);
		if (!dir)
			return (NULL);
		full_path = join_path(dir, cmd);
		free(dir);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		dir_start = dir_end + 1;
	}
	return (NULL);
}
