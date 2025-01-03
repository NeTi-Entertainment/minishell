/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:41:29 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 15:06:13 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_shell_data	*init_shell_data(char **envp)
{
	t_shell_data	*shell_data;

	shell_data = malloc(sizeof(t_shell_data));
	if (!shell_data)
		return (NULL);
	shell_data->env = init_env(envp);
	shell_data->cmd = NULL;
	shell_data->last_exit_status = 0;
	return (shell_data);
}

int	initialize_shell(t_shell_data **shell, char **envp)
{
	init_signals();
	*shell = init_shell_data(envp);
	if (!*shell)
		return (1);
	initialize_shlvl(&(*shell)->env);
	return (0);
}
