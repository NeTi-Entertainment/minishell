/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:44:07 by caubert           #+#    #+#             */
/*   Updated: 2024/11/26 16:44:07 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_with_error(char *arg, t_shell_data *shell_data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	rl_clear_history();
	ft_cleanup_shell(&shell_data);
	exit(2);
}

static int	check_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_numeric_exit(char *arg, t_shell_data *shell_data)
{
	long	num;

	num = ft_atol(arg);
	if ((arg[0] == '-' && num > 0) || (arg[0] != '-' && num < 0))
		exit_with_error(arg, shell_data);
	rl_clear_history();
	ft_cleanup_shell(&shell_data);
	exit((num % 256 + 256) % 256);
}

static int	handle_too_many_args(t_shell_data *shell_data)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	shell_data->last_exit_status = 1;
	return (shell_data->last_exit_status);
}

int	builtin_exit(t_cmd *cmd, t_shell_data *shell_data)
{
	int		status;

	if (!cmd->prev && !cmd->next)
		ft_putendl_fd("exit", 2);
	if (cmd->arg_count >= 2)
	{
		if (!check_numeric_arg(cmd->args[1]))
			exit_with_error(cmd->args[1], shell_data);
		if (cmd->arg_count > 2)
			return (handle_too_many_args(shell_data));
		handle_numeric_exit(cmd->args[1], shell_data);
	}
	status = shell_data->last_exit_status;
	rl_clear_history();
	ft_cleanup_shell(&shell_data);
	exit(status);
}
