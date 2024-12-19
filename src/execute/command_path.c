/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:32:09 by caubert           #+#    #+#             */
/*   Updated: 2024/11/26 12:32:09 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*try_path_access(const char *dir, const char *cmd)
{
	char	*full_path;
	char	*dir_copy;

	dir_copy = ft_strdup(dir);
	if (!dir_copy)
		return (NULL);
	full_path = join_path(dir_copy, cmd);
	free(dir_copy);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*check_single_path(char *dir_start, const char *cmd)
{
	char	*dir;
	char	*result;
	char	*dir_end;

	dir_end = ft_strchr(dir_start, ':');
	if (!dir_end)
		return (try_path_access(dir_start, cmd));
	dir = ft_strndup(dir_start, dir_end - dir_start);
	if (!dir)
		return (NULL);
	result = try_path_access(dir, cmd);
	free(dir);
	return (result);
}

char	*search_in_path(char *path_env, const char *cmd)
{
	char	*dir_start;
	char	*result;

	dir_start = path_env;
	while (*dir_start)
	{
		while (*dir_start == ':')
			dir_start++;
		result = check_single_path(dir_start, cmd);
		if (result)
			return (result);
		dir_start = ft_strchr(dir_start, ':');
		if (!dir_start)
			break ;
		dir_start++;
	}
	return (NULL);
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

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	return (search_in_path(path_env, cmd));
}
