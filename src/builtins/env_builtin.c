/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:37:44 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:21:44 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_env(t_shell_data *shell_data)
{
	t_env	*env;

	if (shell_data->cmd->arg_count > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		shell_data->last_exit_status = 1;
		return ;
	}
	env = shell_data->env;
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	shell_data->last_exit_status = 0;
}
