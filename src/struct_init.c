/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:41:03 by caubert           #+#    #+#             */
/*   Updated: 2024/10/08 15:00:39 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	ta->quoted = malloc(sizeof(int) * 10);
	if (!ta->quoted)
	{
		free(ta->tokens);
		free(ta);
		return (NULL);
	}
	ta->second_quote = 0;
	ta->count = 0;
	ta->capacity = 10;
	ta->token = NULL;
	ta->tokensize = 0;
	ta->tokenindex = 0;
	ta->inquotes = 0;
	ta->quotechar = '\0';
	ta->trailing_space = 0;
	return (ta);
}

/* pour if !cmd return null, creer fonction de quit ? */
t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->redirects = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_info = NULL;
	return (cmd);
}

void	fd_info_init(t_cmd *cmd)
{
	if (!cmd->fd_info)
	{
		cmd->fd_info = malloc(sizeof(t_fd_info));
		if (!cmd->fd_info)
			return ;
	}
	cmd->fd_info->stdin_backup = -1;
	cmd->fd_info->stdout_backup = -1;
	cmd->fd_info->pipe_fd[0] = -1;
	cmd->fd_info->pipe_fd[1] = -1;
}
