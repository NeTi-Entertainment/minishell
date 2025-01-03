/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:21:53 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:30:42 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	should_concat(char *prev_arg, char *curr_arg)
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

void	concat_argument(t_cmd *cmd, char *arg)
{
	char	*new_arg;
	int		last_idx;

	last_idx = cmd->arg_count - 1;
	new_arg = ft_strjoin(cmd->args[last_idx], arg);
	if (!new_arg)
		return ;
	free(cmd->args[last_idx]);
	cmd->args[last_idx] = new_arg;
}

void	add_argument(t_cmd *cmd, char *arg, int quoted)
{
	if (cmd->arg_count > 0 && should_concat(cmd->args[cmd->arg_count - 1], arg))
	{
		concat_argument(cmd, arg);
		return ;
	}
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * (cmd->arg_count + 2));
	cmd->arg_quoted = ft_realloc(cmd->arg_quoted, sizeof(char *) * \
			(cmd->arg_count + 2));
	if (!cmd->args || !cmd->arg_quoted)
		return ;
	cmd->args[cmd->arg_count] = ft_strdup(arg);
	cmd->arg_quoted[cmd->arg_count] = quoted;
	if (!cmd->args[cmd->arg_count])
	{
		cmd->args[cmd->arg_count] = NULL;
		return ;
	}
	cmd->args[cmd->arg_count + 1] = NULL;
	cmd->arg_count++;
	if (!cmd->name)
	{
		cmd->name = ft_strdup(arg);
		cmd->quoted = quoted;
	}
}
