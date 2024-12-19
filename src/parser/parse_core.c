/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:22:20 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 19:22:20 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_token(t_cmd *cmd, t_ta *ta, int *i)
{
	if (!handle_pipe_token(cmd, ta, i))
		return (0);
	if (*i < ta->count)
	{
		if (ft_strcmp(ta->tokens[*i], " ") == 0 && \
				!ta->quoted[*i] && !cmd->name)
			return (1);
		if (get_redirect_type(ta->tokens[*i]) >= 0 && !ta->quoted[*i])
			handle_redirect(cmd, ta, i);
		else if (ft_strcmp(ta->tokens[*i], "") == 0)
			handle_empty_token(cmd, ta, i);
		else
			add_argument(cmd, ta->tokens[*i], ta->quoted[*i]);
	}
	return (1);
}

void	handle_redirect(t_cmd *cmd, t_ta *ta, int *i)
{
	int	redirect_type;
	int	next_idx;

	redirect_type = get_redirect_type(ta->tokens[*i]);
	if (redirect_type >= 0 && *i + 1 < ta->count)
	{
		next_idx = *i + 1;
		while (next_idx < ta->count && \
				ft_strcmp(ta->tokens[next_idx], " ") == 0)
			next_idx++;
		if (next_idx < ta->count && ta->tokens[next_idx])
		{
			add_redirect(cmd, redirect_type, ta->tokens[next_idx], \
					ta->quoted[next_idx]);
			*i = next_idx;
		}
	}
}

int	handle_pipe_token(t_cmd *cmd, t_ta *ta, int *i)
{
	if (ft_strcmp(ta->tokens[*i], "|") == 0 && !ta->quoted[*i])
	{
		if (!handle_pipe(cmd, ta, *i))
		{
			free_command(cmd);
			return (0);
		}
		*i = ta->count;
	}
	return (1);
}

void	handle_empty_token(t_cmd *cmd, t_ta *ta, int *i)
{
	char	*tmp;

	if ((*i + 1) < ta->count && ft_isspace(ta->tokens[*i + 1][0]))
	{
		tmp = ft_strdup(ta->tokens[*i + 1]);
		if (tmp)
		{
			add_argument(cmd, tmp, ta->quoted[*i]);
			free(tmp);
			(*i)++;
		}
	}
	else
		add_argument(cmd, "", ta->quoted[*i]);
}

t_cmd	*parse_tokens(t_ta *ta)
{
	t_cmd	*cmd;
	int		i;

	printf("\n===== parse tokens debug =====\n");
	printf("Total tokens: %d\n", ta->count);
	for (int j = 0; j < ta->count; j++)
		printf("Token[%d]: '%s' (quoted: %d)\n", j, ta->tokens[j], ta->quoted[j]);
	printf("===============================\n\n");
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
		if (!process_token(cmd, ta, &i))
			return (NULL);
		i++;
	}
	if (!cmd->name && cmd->arg_count == 0)
	{
		free_command(cmd);
		return (NULL);
	}
	return (cmd);
}
