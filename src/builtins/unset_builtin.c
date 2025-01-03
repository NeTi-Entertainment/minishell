/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:28:20 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:22:28 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_unset_error(char *arg, int has_exclamation)
{
	if (has_exclamation)
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(ft_strchr(arg, '!'), 2);
		ft_putstr_fd("': event not found\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}

static int	is_valid_unset_identifier(const char *str, int *has_exclamation)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_' && str[0] != '$')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '!')
		{
			*has_exclamation = 1;
			return (0);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_unset(t_cmd *cmd, t_shell_data *shell_data)
{
	int	i;
	int	has_exclamation;

	i = 1;
	while (i < cmd->arg_count)
	{
		has_exclamation = 0;
		if (!is_valid_unset_identifier(cmd->args[i], &has_exclamation))
		{
			shell_data->last_exit_status = handle_unset_error(cmd->args[i], \
					has_exclamation);
			return ;
		}
		remove_env_var(&shell_data->env, cmd->args[i]);
		i++;
	}
	shell_data->last_exit_status = 0;
}
