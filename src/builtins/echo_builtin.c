/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:20:19 by caubert           #+#    #+#             */
/*   Updated: 2024/12/17 13:05:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	has_history_expansion(const char *str, int is_quoted)
{
	if (is_quoted)
		return (0);
	while (*str)
	{
		if (*str == '!' && *(str + 1) != '\0')
			return (1);
		str++;
	}
	return (0);
}

static int	check_n_option(char *arg, int n_quoted)
{
	int	i;

	if (!arg || arg[0] != '-' || n_quoted)
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

static int	echo_expansion_error(const char *arg)
{
	char	*excl_pos;

	excl_pos = ft_strchr(arg, '!');
	if (!excl_pos)
		return (1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(excl_pos, 2);
	ft_putendl_fd(": event not found", 2);
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	printf("\n===== Echo debug =====\n");
	printf("Command name: '%s' (quoted: %d)\n", cmd->name, cmd->quoted);
	printf("Arguments:\n");
	i = 0;
	while (i < cmd->arg_count)
	{
		printf("arg[%d]: '%s'\n", i, cmd->args[i]);
		i++;
	}
	printf("========================\n\n");
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && i < cmd->arg_count && \
			check_n_option(cmd->args[i], cmd->n_quoted))
	{
		n_flag = 1;
		i++;
	}
	while (i < cmd->arg_count && cmd->args[i])
	{
		if (has_history_expansion(cmd->args[i], cmd->arg_quoted[i]))
			return (echo_expansion_error(cmd->args[i]));
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
