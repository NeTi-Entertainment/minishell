/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:07:52 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 19:19:41 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	should_concat(char *prev_arg, char *curr_arg)
{
	if (!prev_arg || !curr_arg || !*prev_arg || !*curr_arg)
		return (0);
	if (prev_arg[0] == '$' && (curr_arg[0] == ':' || curr_arg[0] == '$' || \
				curr_arg[0] == '='))
		return (1);
	if (prev_arg[ft_strlen(prev_arg) - 1] == ':' && curr_arg[0] == '$')
		return (1);
	if (prev_arg[ft_strlen(prev_arg) - 1] == '$' && curr_arg[0] == '=')
		return (1);
	if (ft_isdigit(prev_arg[0]) && curr_arg[0] == '$')
		return (1);
	if (prev_arg[ft_strlen(prev_arg) - 1] == '$')
		return (1);
	return (0);
}

void	add_argument(t_cmd *cmd, char *arg)
{
	char	*new_arg;
	int		last_idx;

	if (cmd->arg_count > 0 && should_concat(cmd->args[cmd->arg_count - 1], arg))
	{
		last_idx = cmd->arg_count - 1;
		new_arg = ft_strjoin(cmd->args[last_idx], arg);
		if (!new_arg)
			return ;
		free(cmd->args[last_idx]);
		cmd->args[last_idx] = new_arg;
		return ;
	}
	printf("adding argument: %s\n", arg);
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * (cmd->arg_count + 2));
	if (!cmd->args)
	{
//		free(new_arg);
		return ;
	}
	cmd->args[cmd->arg_count] = ft_strdup(arg);
	printf("argument added at %p: %s\n", cmd->args[cmd->arg_count], cmd->args[cmd->arg_count]);
	if (!cmd->args[cmd->arg_count])
	{
		cmd->args[cmd->arg_count] = NULL; ////
		return ;
	}
	cmd->args[cmd->arg_count + 1] = NULL;
	cmd->arg_count++;
	if (!cmd->name)
	{
		cmd->name = ft_strdup(arg);
	//	if (!cmd->name)//debut d'edit
	//	{
	//		free(cmd->args[cmd->arg_count - 1]);
	//		cmd->args[cmd->arg_count - 1] = NULL;
	//		cmd->arg_count--;
	//		return ;
	//	}
	}
}

void	add_redirect(t_cmd *cmd, int type, char *file)
{
	t_redirect	*new;
	t_redirect	*last;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
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
