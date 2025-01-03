/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:12 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 14:49:15 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_input(void)
{
	char	*line;

	check_and_restore_stdin();
	line = readline(PROMPT);
	if (!line)
	{
		if (read(STDIN_FILENO, NULL, 0) == 0)
			printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

static int	main_loop(t_shell_data *shell)
{
	char	*input;

	while (1)
	{
		input = get_input();
		if (!input)
		{
			if (!is_eof_reached())
				continue ;
			break ;
		}
		if (g_sig == SIGINT)
			update_exit_status(shell);
		if (ft_strlen(input) > 0)
			handle_input(input, shell);
		else
			free(input);
	}
	free(input);
	rl_clear_history();
	return (shell->last_exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_shell_data	*shell;
	int				exit_status;

	(void)ac;
	(void)av;
	if (initialize_shell(&shell, envp))
		return (1);
	exit_status = main_loop(shell);
	ft_cleanup_shell(&shell);
	return (exit_status);
}
