/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:14:58 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:29:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_current_cmd(t_shell_data *shell_data)
{
	if (shell_data->cmd)
	{
		free_command(shell_data->cmd);
		shell_data->cmd = NULL;
	}
}

int	handle_syntax_check(char *input, t_shell_data *shell_data)
{
	if (check_syntax(input) != 0)
	{
		shell_data->last_exit_status = 2;
		free(input);
		return (1);
	}
	return (0);
}

t_cmd	*execute_input(char *input, t_shell_data *shell_data)
{
	char	*expanded_input;
	t_ta	*ta;
	t_cmd	*cmd;
	int		is_empty;

	expanded_input = expand_variables(input, shell_data);
	if (!expanded_input)
		return (NULL);
	is_empty = (expanded_input[0] == '\0');
	ta = lexer(expanded_input);
	free(expanded_input);
	if (!ta && is_empty)
	{
		shell_data->last_exit_status = 0;
		return (NULL);
	}
	if (!ta)
		return (NULL);
	cmd = parse_tokens(ta);
	free_tokenarray(ta);
	return (cmd);
}

void	execute_if_valid(t_cmd *cmd, t_shell_data *sd)
{
	if (cmd)
	{
		sd->cmd = cmd;
		execute_commands(cmd, sd);
	}
}

void	handle_input(char *input, t_shell_data *shell_data)
{
	t_cmd	*cmd;

	if (!input)
		exit(0);
	if (handle_syntax_check(input, shell_data))
		return ;
	cleanup_current_cmd(shell_data);
	cmd = execute_input(input, shell_data);
	free(input);
	execute_if_valid(cmd, shell_data);
}
