/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenarray_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:01:31 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:31:19 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ta	*init_new_ta(t_ta *ta, int index)
{
	t_ta	*new_ta;

	new_ta = tokenarray_init();
	if (!new_ta)
		return (NULL);
	free(new_ta->tokens);
	free(new_ta->quoted);
	new_ta->count = ta->count - index - 1;
	return (new_ta);
}

char	**create_sub_tokens(t_ta *ta, int index, t_ta *new_ta)
{
	char	**sub_tokens;
	int		i;

	sub_tokens = malloc(sizeof(char *) * (new_ta->count + 1));
	if (!sub_tokens)
		return (NULL);
	i = 0;
	while (i < new_ta->count)
	{
		sub_tokens[i] = ft_strdup(ta->tokens[index + 1 + i]);
		if (!sub_tokens[i])
			return (NULL);
		i++;
	}
	sub_tokens[i] = NULL;
	return (sub_tokens);
}

int	init_quoted_array(t_ta *new_ta, t_ta *ta, int index)
{
	int	i;

	new_ta->quoted = malloc(sizeof(int) * new_ta->count);
	if (!new_ta->quoted)
		return (0);
	i = 0;
	while (i < new_ta->count)
	{
		new_ta->quoted[i] = ta->quoted[index + 1 + i];
		i++;
	}
	return (1);
}
