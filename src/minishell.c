/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:28:40 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 13:08:49 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_exit_code = 0;

static char	*get_input(void)
{
	char		*line;

	line = readline(PROMPT);
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

static void	handle_input(char *input, t_shell_data *shell_data)
{
	t_ta	*ta;
	t_cmd	*cmd;
	char	*expanded_input;
	int		backup_g; //ajout de backup pour globale

	if (!input)
	{
		rl_clear_history();
		exit(0);
	}
	backup_g = g_exit_code; //assignation a la globale
	if (check_syntax(input) != 0)
	{
		shell_data->last_exit_status = 2;
		free(input);
		return ;
	}
	expanded_input = expand_variables(input, shell_data);
	free(input);
	if (!expanded_input)
		return ;
	ta = lexer(expanded_input);
	free(expanded_input);
	if (!ta)
		return ;
	cmd = parse_tokens(ta);
	free_tokenarray(ta);
	if (cmd)
	{
		execute_commands(cmd, shell_data);
		free_command(cmd);
		if (g_exit_code != backup_g)
			shell_data->last_exit_status = g_exit_code;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell_data	*shell;
	char			*input;

	(void)ac;
	(void)av;
	(void)envp;
	init_signals();
	shell = get_shell_data();
	if (!shell)
		return (1);
	while (1)
	{
		input = get_input();
		if (input == NULL)
			break ;
		if (ft_strlen(input) > 0)
		{
			handle_input(input, shell);
			g_exit_code = shell->last_exit_status;
		}
		else
			free(input);
	}
	rl_clear_history();
	ft_cleanup_shell(&shell);
	return (g_exit_code);
}
