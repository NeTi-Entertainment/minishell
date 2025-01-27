/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:20:03 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:23:13 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_pwd(t_cmd *cmd)
{
	char	*pwd;
	char	*arg;

	arg = cmd->args[1];
	if ((arg && arg[0] == '-' && arg[1] && arg[1] != '-') || \
			(arg && arg[0] == '-' && arg[1] == '-' && arg[2]))
	{
		ft_putstr_fd("minishell: pwd: -", 2);
		ft_putchar_fd(arg[1], 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
