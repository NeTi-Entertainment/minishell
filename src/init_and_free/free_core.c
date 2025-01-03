/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:27:34 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:28:27 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_tokenarray(t_ta *ta)
{
	int	i;

	if (!ta)
		return ;
	if (ta->tokens)
	{
		i = 0;
		while (i < ta->count)
		{
			if (ta->tokens[i])
				free(ta->tokens[i]);
			i++;
		}
		free(ta->tokens);
	}
	if (ta->quoted)
		free(ta->quoted);
	if (ta->token)
		free(ta->token);
	free(ta);
}

void	free_redirects(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		free(redirect->file);
		free(redirect);
		redirect = temp;
	}
}
