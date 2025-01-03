/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:49:16 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:27:57 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_quotes(const char *str)
{
	if ((str[0] == '"' || str[0] == '\'') && str[1] != '\0')
		return (1);
	return (0);
}

void	copy_var_value(char **result, int *j, char *var_value)
{
	(*result)[*j] = '"';
	(*j)++;
	ft_strcpy(*result + *j, var_value);
	*j += ft_strlen(var_value);
	(*result)[*j] = '"';
	(*j)++;
}

int	get_quoted_length(const char *str)
{
	int		i;
	char	quote_char;

	i = 1;
	quote_char = str[0];
	if (!str[i])
		return (0);
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == quote_char)
		return (i);
	return (0);
}

int	handle_quoted_var(char **result, int *j, char *input)
{
	int		quote_len;
	int		is_quoted;

	if (!input[1])
	{
		(*result)[(*j)++] = *input;
		return (0);
	}
	if (input[1] == '\'')
		return (0);
	is_quoted = 0;
	quote_len = get_quoted_length(input + 1);
	if (input > (char *)1)
		is_quoted = is_in_quotes(input);
	if (is_quoted)
	{
		(*result)[(*j)++] = *input;
		return (0);
	}
	return (handle_quoted_len(result, j, input, quote_len));
}

int	handle_var(char **res, int *j, char *in, t_shell_data *sd)
{
	int		var_len;
	char	*var_value;
	char	var_name[256];

	if (is_in_quotes(in + 1))
		return (handle_quoted_var(res, j, in));
	var_len = get_var_length(in + 1);
	if (var_len > 0)
	{
		ft_strncpy(var_name, in + 1, var_len);
		var_name[var_len] = '\0';
		var_value = get_var_value(var_name, sd);
		if (var_value)
		{
			copy_var_value(res, j, var_value);
			if (ft_strcmp(var_name, "?") == 0)
				free(var_value);
		}
		return (var_len);
	}
	(*res)[(*j)++] = *in;
	return (0);
}
