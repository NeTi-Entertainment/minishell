/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:43:26 by caubert           #+#    #+#             */
/*   Updated: 2024/12/04 19:43:26 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
