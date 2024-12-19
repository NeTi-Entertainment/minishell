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
	char	*arg;

	arg = get_shell_data()->cmd->args[1];
	if ((arg && arg[0] == '-' && arg[1] && arg[1] != '-') || \
			(arg && arg[0] == '-' && arg[1] == '-' && arg[2]))
	{
		ft_putstr_fd("minishell: pwd: -", 2);
		ft_putchar_fd(arg[1], 2);
		ft_putendl_fd(": invalid option", 2);
		get_shell_data()->last_exit_status = 2;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
		get_shell_data()->last_exit_status = 0;
	}
	else
	{
		perror("pwd");
		get_shell_data()->last_exit_status = 1;
	}
}
