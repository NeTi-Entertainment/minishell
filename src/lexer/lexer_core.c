/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:16:13 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:29:04 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_char(t_ta *ta, char **input)
{
	if (ta->tokenindex == ta->tokensize)
	{
		if (ta->tokensize == 0)
			ta->tokensize = 1;
		else
			ta->tokensize = ta->tokensize * 2;
		ta->token = ft_realloc(ta->token, ta->tokensize + 1);
		if (!ta->token)
			return ;
	}
	if (**input == '"' || **input == '\'' || ta->inquotes)
		process_quotes(ta, input);
	else if (**input == ' ' || **input == '\t')
		handle_token_end(ta);
	else if (!ta->inquotes && ft_strchr("<>|$", **input))
		handle_special_chars(ta, input);
	else
		ta->token[ta->tokenindex++] = **input;
}

void	process_input(t_ta *ta, char *input)
{
	while (*input)
	{
		process_char(ta, &input);
		input++;
	}
	handle_token_end(ta);
}

void	handle_token_end(t_ta *ta)
{
	int		was_quoted;

	was_quoted = ta->second_quote;
	if (ta->tokenindex > 0 || ta->trailing_space)
	{
		if (ta->count >= ta->capacity)
			resize_token_array(ta);
		ta->token[ta->tokenindex] = '\0';
		if (ta->trailing_space && ta->tokenindex == 0)
			handle_trailing_space(ta, was_quoted);
		else
		{
			ta->quoted[ta->count] = was_quoted;
			add_token(ta, ta->token);
		}
		ta->tokenindex = 0;
		ta->second_quote = 0;
	}
}

int	add_token(t_ta *ta, char *token)
{
	char	**new_tokens;
	int		*new_quoted;

	if (ta->count == ta->capacity)
	{
		ta->capacity *= 2;
		new_tokens = ft_realloc(ta->tokens, sizeof(char *) * ta->capacity);
		new_quoted = ft_realloc(ta->quoted, sizeof(int) * ta->capacity);
		if (!new_tokens || !new_quoted)
		{
			free(ta->tokens);
			free(ta->quoted);
			ta->tokens = NULL;
			ta->quoted = NULL;
			return (1);
		}
		ta->tokens = new_tokens;
		ta->quoted = new_quoted;
	}
	ta->tokens[ta->count] = ft_strdup(token);
	if (!ta->tokens[ta->count])
		return (1);
	ta->quoted[ta->count] = ta->second_quote;
	ta->count++;
	return (0);
}

t_ta	*lexer(char *input)
{
	t_ta	*ta;

	ta = tokenarray_init();
	if (!ta)
		return (NULL);
	if (is_only_quotes(input))
		return (create_special_empty_token(ta));
	process_input(ta, input);
	if (ta->tokenindex > 0)
	{
		ta->token[ta->tokenindex] = '\0';
		if (add_token(ta, ta->token))
		{
			free_tokenarray(ta);
			return (NULL);
		}
	}
	if (!ta->count)
	{
		free_tokenarray(ta);
		return (NULL);
	}
	return (ta);
}
