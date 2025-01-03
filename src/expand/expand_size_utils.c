/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_size_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:49:02 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:27:45 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_quoted_len(char **result, int *j, char *input, int quote_len)
{
	if (quote_len == 1 && input[2] == input[1])
		return (quote_len);
	if (quote_len == 1 && input[3])
	{
		ft_memcpy(*result + *j, input + 3, ft_strlen(input + 3));
		*j += ft_strlen(input + 3);
		return (quote_len);
	}
	if (quote_len)
	{
		ft_memcpy(*result + *j, input + 2, quote_len - 1);
		*j += quote_len - 1;
		return (quote_len);
	}
	(*result)[(*j)++] = *input;
	return (0);
}

int	process_var(char *input, int i, size_t *size, t_shell_data *sd)
{
	int		var_len;
	char	var_name[256];
	char	*var_value;

	var_len = get_var_length(input + i + 1);
	if (var_len > 0)
	{
		ft_strncpy(var_name, input + i + 1, var_len);
		var_name[var_len] = '\0';
		var_value = get_var_value(var_name, sd);
		if (var_value)
			*size += ft_strlen(var_value) + 2;
		else
			(*size)++;
		if (var_value && ft_strcmp(var_name, "?") == 0)
			free(var_value);
		return (var_len);
	}
	(*size)++;
	return (0);
}
