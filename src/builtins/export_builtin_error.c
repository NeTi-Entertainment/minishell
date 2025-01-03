/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:44:00 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:23:04 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	export_event_error(char *full_arg)
{
	char	*excl_part;

	ft_putstr_fd("minishell: ", 2);
	excl_part = get_exclamation_part(full_arg);
	if (excl_part)
	{
		ft_putstr_fd(excl_part, 2);
		free(excl_part);
	}
	ft_putendl_fd(": event not found", 2);
}
