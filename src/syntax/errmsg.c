/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:26:22 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 13:25:04 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errmsg(char *errmsg, char *detail, int quotes)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(errmsg, 2);
	if (quotes)
		ft_putstr_fd(" '", 2);
	else
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(detail, 2);
	if (quotes)
		ft_putstr_fd("'", 2);
	ft_putchar_fd('\n', 2);
	g_exit_code = 2;
	return (1);
}
