/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:21:01 by caubert           #+#    #+#             */
/*   Updated: 2024/11/17 01:21:01 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_only_path_chars(char *input)
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
