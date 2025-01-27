/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:16:38 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:29:28 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_trailing_space(t_ta *ta, int was_quoted)
{
	char	*tmp;

	if (ta->tokenindex == 0)
	{
		ta->token[0] = ' ';
		ta->token[1] = '\0';
		add_token(ta, ta->token);
	}
	else
	{
		tmp = ft_strjoin(ta->token, " ");
		if (tmp)
		{
			ta->quoted[ta->count] = was_quoted;
			add_token(ta, tmp);
			free(tmp);
		}
	}
	ta->trailing_space = 0;
}

static void	process_special_token(t_ta *ta, char **input)
{
	if ((**input == '<' && *(*input + 1) == '<') || \
		(**input == '>' && *(*input + 1) == '>'))
	{
		ta->token[1] = **input;
		ta->token[2] = '\0';
		(*input)++;
	}
	else
		ta->token[1] = '\0';
	add_token(ta, ta->token);
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
		process_special_token(ta, input);
	}
}

void	resize_token_array(t_ta *ta)
{
	int		new_capacity;
	char	**new_tokens;
	int		*new_quoted;
	int		i;

	new_capacity = ta->capacity * 2;
	new_tokens = ft_realloc(ta->tokens, ta->capacity * sizeof(char *), \
			new_capacity * sizeof(char *));
	new_quoted = ft_realloc(ta->quoted, ta->capacity * sizeof(int), \
			new_capacity * sizeof(int));
	if (!new_tokens || !new_quoted)
		return ;
	ta->tokens = new_tokens;
	ta->quoted = new_quoted;
	i = ta->capacity;
	while (i < new_capacity)
	{
		ta->tokens[i] = NULL;
		ta->quoted[i] = 0;
		i++;
	}
	ta->capacity = new_capacity;
}
