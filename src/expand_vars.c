/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:21:50 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 13:05:48 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_var_value(const char *var, t_shell_data *shell_data)
{
	char	*exit_status;

	if (ft_strcmp(var, "?") == 0)
	{
		exit_status = ft_itoa(shell_data->last_exit_status);
		if (!exit_status)
			return (NULL);
		return (exit_status);
	}
	return (get_env_value(shell_data->env, var));
}

static int	get_var_length(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static void	copy_var_value(char **result, int *j, char *var_value)
{
	ft_strcpy(*result + *j, var_value);
	*j += ft_strlen(var_value);
	free(var_value);
}

static int	get_quoted_length(const char *str)
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

static int	is_in_quotes(const char *str)
{
	if ((str[0] == '"' || str[0] == '\'') && str[1] != '\0')
		return (1);
	return (0);
}

static int	handle_quoted_var(char **result, int *j, char *input)
{
	int		quoted_len;
	int		is_quoted;

	if (!input[1])
	{
		(*result)[(*j)++] = *input;
		return (0);
	}
	quoted_len = get_quoted_length(input + 1);
	is_quoted = is_in_quotes(input - 1);
	if (is_quoted)
	{
		(*result)[(*j)++] = *input;
		return (0);
	}
	if (quoted_len == 1 && input[2] == input[1])
		return (quoted_len);
	if (quoted_len == 1 && input[3])
	{
		ft_memcpy(*result + *j, input + 3, ft_strlen(input + 3));
		*j += ft_strlen(input + 3);
		return (quoted_len);
	}
	if (quoted_len)
	{
		ft_memcpy(*result + *j, input + 2, quoted_len - 1);
		*j += quoted_len - 1;
		return (quoted_len);
	}
	(*result)[(*j)++] = *input;
	return (0);
}

/* in = input, sd = shell_data */
static int	handle_var(char **res, int *j, char *in, t_shell_data *sd)
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
			copy_var_value(res, j, var_value);
		return (var_len);
	}
	(*res)[(*j)++] = *in;
	return (0);
}

size_t	calculate_expanded_size(char *input, t_shell_data *shell_data)
{
	size_t	size;
	int		i;
	int		in_squote;
	int		var_len;
	char	var_name[256];
	char	*var_value;

	size = 0;
	i = 0;
	in_squote = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			in_squote = !in_squote;
		if (input[i] == '$' && !in_squote && input[i + 1])
		{
			var_len = get_var_length(input + i + 1);
			if (var_len > 0)
			{
				ft_strncpy(var_name, input + i + 1, var_len);
				var_name[var_len] = '\0';
				var_value = get_var_value(var_name, shell_data);
				if (var_value)
				{
					size += ft_strlen(var_value);
					if (ft_strcmp(var_name, "?") == 0)
						free(var_value);
				}
				i += var_len;
			}
			else
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*expand_variables(char *input, t_shell_data *shell_data)
{
	char	*result;
	int		in_squote;
	int		in_dquote;
	int		i;
	int		j;
	size_t	needed_size;

	needed_size = calculate_expanded_size(input, shell_data);
	result = malloc(sizeof(char) * (needed_size + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		if (input[i] == '$' && !in_squote && input[i + 1])
			i += handle_var(&result, &j, input + i, shell_data);
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
