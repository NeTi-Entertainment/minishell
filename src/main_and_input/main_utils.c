/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonia <sonia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:43:26 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:30:24 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_shlvl(t_env **env, int level)
{
	char	*new_level;

	new_level = ft_itoa(level);
	if (!new_level)
		return ;
	set_env_value(env, "SHLVL", new_level);
	free(new_level);
}

void	initialize_shlvl(t_env **env)
{
	char		*shlvl;
	int			level;

	level = 0;
	shlvl = get_env_value(*env, "SHLVL");
	if (!shlvl || !*shlvl)
		update_shlvl(env, 1);
	else
		level = ft_atoi(shlvl);
	update_shlvl(env, level + 1);
}

void	check_and_restore_stdin(void)
{
	int	fd;

	if (isatty(STDIN_FILENO) == 0)
	{
		fd = open("/dev/tty", O_RDONLY);
		if (fd == -1)
			exit(1);
		if (dup2(fd, STDIN_FILENO) == -1)
			exit(1);
		close(fd);
	}
}

int	is_eof_reached(void)
{
	char	buffer[1];
	int		bytes_read;

	bytes_read = read(STDIN_FILENO, buffer, 0);
	return (bytes_read == 0);
}
