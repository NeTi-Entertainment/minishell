/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:17:21 by caubert           #+#    #+#             */
/*   Updated: 2024/11/26 16:17:21 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_error(char *identifier, char *arg, t_shell_data *sd)
{
	if (identifier[0] == '-')
	{
		ft_putstr_fd("minishell: export: -", 2);
		if (identifier[1])
			ft_putchar_fd(identifier[1], 2);
		ft_putendl_fd(": invalid option", 2);
		sd->last_exit_status = 2;
		return ;
	}
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	sd->last_exit_status = 1;
}

int	check_exclamation_export(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '!')
			return (1);
		str++;
	}
	return (0);
}

int	is_valid_first_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_identifier_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str || !is_valid_first_char(str[0]))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!is_valid_identifier_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}
