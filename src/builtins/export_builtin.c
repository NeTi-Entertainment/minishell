/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:58:04 by caubert           #+#    #+#             */
/*   Updated: 2024/12/17 14:54:00 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_export_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(current->key, 2);
		ft_putstr_fd("=\"", 2);
		ft_putstr_fd(current->value, 2);
		ft_putendl_fd("\"", 2);
		current = current->next;
	}
}

static char	*get_exclamation_part(const char *str)
{
	char	*temp;
	char	*dollar;
	char	*excl;

	excl = ft_strchr(str, '!');
	if (!excl)
		return (NULL);
	dollar = ft_strchr(excl, '$');
	if (!dollar)
		return (ft_strdup(excl));
	temp = ft_strndup(excl, dollar - excl);
	return (temp);
}

/* k = key, v = value, fa = full_arg, sd = shell_data */
static int	handle_export_value(char *k, char *v, char *fa, t_shell_data *sd)
{
	char	*excl_part;

	if (!k)
	{
		print_export_list(sd->env);
		return (0);
	}
	if (check_exclamation_export(k) || (v && check_exclamation_export(v)))
	{
		ft_putstr_fd("minishell: ", 2);
		excl_part = get_exclamation_part(fa);
		if (excl_part)
		{
			ft_putstr_fd(excl_part, 2);
			free(excl_part);
		}
		ft_putendl_fd(": event not found", 2);
		return (2);
	}
	if (!is_valid_identifier(k))
	{
		export_error(k, fa, sd);
		return (1);
	}
	if (v)
		set_env_value(&sd->env, k, v);
	return (0);
}

static int	process_export_arg(char *arg, t_shell_data *shell_data)
{
	char	*key;
	char	*value;
	char	*full_arg;
	int		result;

	if (arg[0] == '=')
	{
		export_error(arg, arg, shell_data);
		return (1);
	}
	full_arg = ft_strdup(arg);
	if (!full_arg)
		return (1);
	key = arg;
	value = ft_strchr(key, '=');
	if (value)
	{
		*value = '\0';
		value++;
		if (!*value && shell_data->cmd->arg_count > 2)
		{
			value = shell_data->cmd->args[2];
			if (ft_strcmp(value, "$") == 0)
				value = "$";
		}
	}
	result = handle_export_value(key, value, full_arg, shell_data);
	free(full_arg);
	return (result);
}

int	builtin_export(t_cmd *cmd, t_shell_data *shell_data)
{
	int	i;
	int	result;

	i = 1;
	shell_data->last_exit_status = 0;
	if (cmd->arg_count == 1)
	{
		print_export_list(shell_data->env);
		return (0);
	}
	while (i < cmd->arg_count)
	{
		result = process_export_arg(cmd->args[i], shell_data);
		if (result == 2)
			shell_data->last_exit_status = 2;
		else if (result == 1)
			shell_data->last_exit_status = 1;
		i++;
	}
	return (shell_data->last_exit_status);
}
