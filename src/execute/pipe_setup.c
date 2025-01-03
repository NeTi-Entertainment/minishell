/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:43:57 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:25:03 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*setup_pipe_cmd(t_ta *new_ta, t_ta *ta, int idx, char **stok)
{
	t_cmd	*next_cmd;

	new_ta->tokens = stok;
	if (!init_quoted_array(new_ta, ta, idx))
	{
		cleanup_pipe_data(new_ta, stok, new_ta->count);
		return (NULL);
	}
	next_cmd = parse_tokens(new_ta);
	free_tokenarray(new_ta);
	return (next_cmd);
}

int	handle_pipe(t_cmd *cmd, t_ta *ta, int index)
{
	t_ta	*new_ta;
	t_cmd	*next_cmd;
	char	**sub_tokens;

	if (index + 1 >= ta->count)
		return (0);
	new_ta = init_new_ta(ta, index);
	if (!new_ta)
		return (0);
	sub_tokens = create_sub_tokens(ta, index, new_ta);
	if (!sub_tokens)
	{
		cleanup_pipe_data(new_ta, NULL, 0);
		return (0);
	}
	next_cmd = setup_pipe_cmd(new_ta, ta, index, sub_tokens);
	if (!next_cmd)
		return (0);
	next_cmd->prev = cmd;
	cmd->next = next_cmd;
	return (1);
}
