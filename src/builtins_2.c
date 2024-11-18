/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:20:03 by caubert           #+#    #+#             */
/*   Updated: 2024/10/16 13:57:51 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
	}
	else
		perror("pwd");
}

void	builtin_unset(t_cmd *cmd, t_shell_data *shell_data)
{
	int	i;

	i = 1;
	while (i < cmd->arg_count)
	{
		remove_env_var(&shell_data->env, cmd->args[i]);
		i++;
	}
	shell_data->last_exit_status = 0;
}
