/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:20:19 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 14:10:15 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//volatile sig_atomic_t	g_exit_code;

int	builtin_cd(t_cmd *cmd, t_shell_data *shell_data)
{
	char	*path;

	g_exit_code = 0;
	if (cmd->arg_count > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (cmd->arg_count == 1)
	{
		path = get_env_value(shell_data->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_exit_code = 1;
			return (g_exit_code);
		}
	}
	else
		path = cmd->args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exit_code = 1;
	}
	else
		shell_data->last_exit_status = 0;
	return (g_exit_code);
}

static int	check_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && i < cmd->arg_count && \
			check_n_option(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (i < cmd->arg_count && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (i < cmd->arg_count - 1 && \
				cmd->args[i][ft_strlen(cmd->args[i]) - 1] != ' ' && \
				ft_strcmp(cmd->args[i + 1], " ") != 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	builtin_env(t_shell_data *shell_data)
{
	t_env	*env;

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

int	builtin_exit(t_cmd *cmd, t_shell_data *shell_data)
{
	long	num;
	char	*arg;
	int		i;

	if (cmd->arg_count >= 2)
	{
		arg = cmd->args[1];
		i = 0;
		if (arg[0] == '-' || arg[0] == '+')
			i++;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
			{
				ft_putendl_fd("exit: numeric argument required", 2);
				exit(2);
			}
			i++;
		}
		num = ft_atol(arg);
		if (cmd->arg_count > 2)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			g_exit_code = 1;
			shell_data->last_exit_status = 1;
			return (1);
		}
		exit((num % 256 + 256) % 256);
	}
	exit(shell_data->last_exit_status);
}

static void	export_error(char *identifier, t_shell_data *shell_data)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell_data->last_exit_status = 1;
}

int	builtin_export(t_cmd *cmd, t_shell_data *shell_data)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	g_exit_code = 0;
	while (i < cmd->arg_count)
	{
		key = cmd->args[i];
		if (!is_valid_identifier(key))
		{
			export_error(key, shell_data);
			return (g_exit_code);
		}
		value = ft_strchr(key, '=');
		if (value)
		{
			*value = '\0';
			value++;
			set_env_value(&shell_data->env, key, value);
		}
		i++;
	}
	g_exit_code = 0;
	return (shell_data->last_exit_status);
}
