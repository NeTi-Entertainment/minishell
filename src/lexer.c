/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:21:08 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 17:07:54 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_empty_quotes(t_ta *ta, char **input)
{
	(*input)++;
	if (**input && !ft_isspace(**input))
		ta->trailing_space = 0;
}

static void	handle_token_end(t_ta *ta)
{
	char	*tmp;
	int		was_quoted;

	was_quoted = ta->second_quote;
	if (ta->tokenindex > 0 || ta->trailing_space)
	{
		ta->token[ta->tokenindex] = '\0';
		if (ta->trailing_space && ta->tokenindex == 0)
		{
			ta->token[0] = ' ';
			ta->token[1] = '\0';
			add_token(ta, ta->token);
			ta->trailing_space = 0;
		}
		else if (ta->trailing_space)
		{
			tmp = ft_strjoin(ta->token, " ");
			if (tmp)
			{
				ta->quoted[ta->count] = was_quoted;
				add_token(ta, tmp);
				free(tmp);
			}
			ta->trailing_space = 0;
		}
		else
		{
			ta->quoted[ta->count] = was_quoted;
			add_token(ta, ta->token);
		}
		ta->tokenindex = 0;
		ta->second_quote = 0;
	}
}

void	process_quotes(t_ta *ta, char **input)
{
	if ((!ta->inquotes) && ((**input == '"' && *(*input + 1) == '"') || \
				(**input == '\'' && *(*input + 1) == '\'')))
	{
		if (*(*input + 2) && ft_isspace(*(*input + 2)))
			ta->trailing_space = 1;
		*input += 1;
		return ;
	}
	handle_quotes(ta, *input);
	if (!ta->inquotes && *(*input + 1) && ft_isspace(*(*input + 1)))
		ta->trailing_space = 1;
}

void	handle_special_chars(t_ta *ta, char **input)
{
	char	*spe;

	spe = "<>|$";
	if (ta->second_quote)
	{
		ta->token[ta->tokenindex++] = **input;
		return ;
	}
	if (ft_strchr(spe, **input))
	{
		if (ta->tokenindex > 0)
		{
			ta->token[ta->tokenindex] = '\0';
			add_token(ta, ta->token);
			ta->tokenindex = 0;
		}
		ta->token[0] = **input;
		ta->token[1] = '\0';
		add_token(ta, ta->token);
		if ((**input == '<' && *(*input + 1) == '<') || \
			(**input == '>' && *(*input + 1) == '>'))
			(*input)++;
	}
}

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
	else if (ft_isspace(**input))
		handle_token_end(ta);
	else if (!ta->inquotes && ft_strchr("<>|$", **input))
		handle_special_chars(ta, input);
	else
		ta->token[ta->tokenindex++] = **input;
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
	ta->quoted[ta->count] = ta->second_quote;
	if (!ta->tokens[ta->count])
		return (1);
	ta->count++;
	return (0);
}

void	handle_quotes(t_ta *ta, char *input)
{
	int	was_quoted;

	if ((*input == '"' || *input == '\''))
	{
		if (!ta->inquotes)
		{
			ta->inquotes = 1;
			ta->quotechar = *input;
			ta->second_quote = 1;
		}
		else if (*input == ta->quotechar)
		{
			was_quoted = ta->inquotes;
			ta->inquotes = 0;
			ta->quotechar = '\0';
			ta->second_quote = was_quoted;
		}
		else
			ta->token[ta->tokenindex++] = *input;
	}
	else
		ta->token[ta->tokenindex++] = *input;
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

t_ta	*lexer(char *input)
{
	t_ta	*ta;

	ta = tokenarray_init();
	if (!ta)
		return (NULL);
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
