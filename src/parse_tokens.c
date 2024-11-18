/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:24:15 by caubert           #+#    #+#             */
/*   Updated: 2024/10/14 15:38:35 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_redirect(t_cmd *cmd, t_ta *ta, int *i)
{
	int	redirect_type;

	redirect_type = get_redirect_type(ta->tokens[*i]);
	if (redirect_type >= 0 && *i + 1 < ta->count)
	{
		add_redirect(cmd, redirect_type, ta->tokens[*i + 1]);
		(*i)++;
	}
}

static void	cleanup_pipe_data(t_ta *new_ta, char **sub_tokens, int last_alloc)
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

static int	handle_pipe(t_cmd *cmd, t_ta *ta, int index)
{
	t_ta	*new_ta;
	t_cmd	*next_cmd;
	int		i;
	char	**sub_tokens;

	if (index + 1 >= ta->count)
		return (0);
	new_ta = tokenarray_init();
	if (!new_ta)
		return (0);
	free(new_ta->tokens);
	free(new_ta->quoted);
	new_ta->count = ta->count - index - 1;
	sub_tokens = malloc(sizeof(char *) * (new_ta->count + 1));
	if (!sub_tokens)
	{
		cleanup_pipe_data(new_ta, NULL, 0);
		return (0);
	}
	i = 0;
	while (i < new_ta->count)
	{
		sub_tokens[i] = ft_strdup(ta->tokens[index + 1 + i]);
		if (!sub_tokens[i])
		{
			cleanup_pipe_data(new_ta, sub_tokens, i);
			return (0);
		}
		i++;
	}
	sub_tokens[i] = NULL;
	new_ta->tokens = sub_tokens;
	if (!(new_ta->quoted = malloc(sizeof(int) * new_ta->count)))
	{
		cleanup_pipe_data(new_ta, sub_tokens, new_ta->count);
		return (0);
	}
	i = 0;
	while (i < new_ta->count)
	{
		new_ta->quoted[i] = ta->quoted[index + 1 + i];
		i++;
	}
	next_cmd = parse_tokens(new_ta);
	free_tokenarray(new_ta);
	if (!next_cmd)
		return (0);
	next_cmd->prev = cmd;
	cmd->next = next_cmd;
	return (1);
}

/*
static void	parse_single_token(t_cmd *cmd, t_ta *ta, int *i)
{
	if (ft_strcmp(ta->tokens[*i], "|") == 0)
	{
		if (handle_pipe(cmd, ta, *i))
			*i = ta->count;
	}
	else if (get_redirect_type(ta->tokens[*i]) >= 0)
		handle_redirect(cmd, ta, i);
	else
		add_argument(cmd, ta->tokens[*i]);
}
*/

t_cmd	*parse_tokens(t_ta *ta)
{
	t_cmd	*cmd;
	int		i;
	char	*tmp;

	if (!ta || !ta->tokens)
		return (NULL);
	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < ta->count && ft_strcmp(ta->tokens[i], "") == 0)
		i++;
	while (i < ta->count)
	{
		if (ft_strcmp(ta->tokens[i], "|") == 0 && !ta->quoted[i])
		{
			if (!handle_pipe(cmd, ta, i))
			{
				free_command(cmd);
				return (NULL);
			}
			i = ta->count;
		}
		else if (get_redirect_type(ta->tokens[i]) >= 0 && !ta->quoted[i])
			handle_redirect(cmd, ta, &i);
		else if (ft_strcmp(ta->tokens[i], "") == 0)
		{
			if (i + 1 < ta->count && ft_isspace(ta->tokens[i + 1][0]))
			{
				tmp = ft_strdup(ta->tokens[i + 1]);
				if (tmp)
				{
					add_argument(cmd, tmp);
					free(tmp);
					i++;
				}
			}
			else
				add_argument(cmd, "");
		}
		else
			add_argument(cmd, ta->tokens[i]);
		i++;
	}
	if (!cmd->name && cmd->arg_count == 0)
	{
		free_command(cmd);
		return (NULL);
	}
	return (cmd);
}
