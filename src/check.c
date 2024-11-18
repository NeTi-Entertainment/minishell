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

static int	check_multi_redir(char *input, int *i)
{
	int	count;

	count = 1;
	while (input[*i + count] && (input[*i + count] == input[*i]))
		count++;
	if (count > 2)
	{
		if (count > 3)
		{
			if (input[*i] == '>')
				ft_putendl_fd("minishell: syntax error near unexpected token '>>'", 2);
			else
				ft_putendl_fd("minishell: syntax error near unexpected token '<<'", 2);
			return (1);
		}
		if (input[*i] == '>')
			ft_putendl_fd("minishell: syntax error near unexpected token '>'", 2);
		else
			ft_putendl_fd("minishell: syntax error near unexpected token '<'", 2);
		return (1);
	}
	*i += count - 1;
	return (0);
}

static int	check_newline_after_redir(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (!input[i])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		return (1);
	}
	return (0);
}

static int	check_consecutive_redir(char *input, int *i)
{
	int		j;
	char	first;

	first = input[*i];
	j = *i + 1;
	while (input[j] && ft_isspace(input[j]))
		j++;
	if (input[j] && (input[j] == '<' || input[j] == '>'))
	{
		if (first == input[j])
			ft_putendl_fd("minishell: syntax error near unexpected token '>>'", 2);
		else
			ft_putendl_fd("minishell: syntax error near unexpected token '>'", 2);
		return (1);
	}
	return (0);
}

int	check_syntax(char *input)
{
	int	i;

//	if (check_directory_path(input))
//		return (1);
	if (check_pipe_syntax(input))
		return (1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			if (check_redir_pipe(input, &i))
				return (1);
			if (check_multi_redir(input, &i))
				return (1);
			if (check_newline_after_redir(input, i + 1))
				return (1);
			if (check_consecutive_redir(input, &i))
				return (1);
			if (check_redir_pipe(input, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

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
