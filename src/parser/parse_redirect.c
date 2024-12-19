/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:22:33 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 19:22:33 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cleanup_pipe_data(t_ta *new_ta, char **sub_tokens, int last_alloc)
{
	int	i;

	if (sub_tokens)
	{
		i = 0;
		while (i < last_alloc)
			free(sub_tokens[i++]);
		free(sub_tokens);
	}
	if (new_ta)
		free_tokenarray(new_ta);
}

int	is_redirect(const char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, "<") == 0)
		return (1);
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	if (ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

int	get_redirect_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (0);
	if (ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, "<<") == 0)
		return (2);
	if (ft_strcmp(token, ">>") == 0)
		return (3);
	return (-1);
}

void	add_redirect(t_cmd *cmd, int type, char *file, int eof_quoted)
{
	t_redirect	*new;
	t_redirect	*last;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->eof_quoted = eof_quoted;
	if (!new->file)
	{
		free(new);
		return ;
	}
	new->next = NULL;
	if (!cmd->redirects)
		cmd->redirects = new;
	else
	{
		last = cmd->redirects;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
