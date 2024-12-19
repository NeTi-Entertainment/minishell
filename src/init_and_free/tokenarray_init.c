/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenarray_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:35:48 by caubert           #+#    #+#             */
/*   Updated: 2024/11/30 03:35:48 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	*alloc_quoted(int capacity)
{
	int	*quoted;

	quoted = malloc(sizeof(int) * capacity);
	if (!quoted)
		return (NULL);
	ft_memset(quoted, 0, sizeof(int) * capacity);
	return (quoted);
}

void	tokenarray_init_second(t_ta *ta)
{
	ta->second_quote = 0;
	ta->count = 0;
	ta->capacity = 10;
	ta->token = NULL;
	ta->tokensize = 0;
	ta->tokenindex = 0;
	ta->inquotes = 0;
	ta->quotechar = '\0';
	ta->trailing_space = 0;
}

t_ta	*tokenarray_init(void)
{
	t_ta	*ta;

	ta = (t_ta *)malloc(sizeof(t_ta));
	if (!ta)
		return (NULL);
	ft_memset(ta, 0, sizeof(t_ta));
	ta->tokens = malloc(sizeof(char *) * 10);
	if (!ta->tokens)
	{
		free(ta);
		return (NULL);
	}
	ta->quoted = alloc_quoted(10);
	if (!ta->quoted)
	{
		free(ta->tokens);
		free(ta);
		return (NULL);
	}
	tokenarray_init_second(ta);
	return (ta);
}
