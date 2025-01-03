/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:16:26 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:29:14 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_only_quotes(const char *input)
{
	if (!input || !*input)
		return (0);
	while (*input)
	{
		if (*input != '"' && *input != '\'')
			return (0);
		input++;
	}
	return (1);
}

t_ta	*create_special_empty_token(t_ta *ta)
{
	ta->tokens[0] = ft_strdup("\"\"");
	if (!ta->tokens[0])
	{
		free_tokenarray(ta);
		return (NULL);
	}
	ta->count = 1;
	ta->quoted[0] = 1;
	return (ta);
}

void	handle_empty_quotes(t_ta *ta, char **input)
{
	(*input)++;
	if (**input && !ft_isspace(**input))
		ta->trailing_space = 0;
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
