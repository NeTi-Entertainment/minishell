/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:12 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 19:15:12 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_exit_code = 0;

char	*get_input(void)
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

t_shell_data	*get_shell_data(void)
{
	static t_shell_data	*shell_data;

	if (!shell_data)
	{
		shell_data = malloc(sizeof(t_shell_data));
		if (!shell_data)
			return (NULL);
		shell_data->env = init_env(__environ);
		shell_data->cmd = NULL;
		shell_data->last_exit_status = 0;
	}
	return (shell_data);
}

int	initialize_shell(t_shell_data **shell)
{
	init_signals();
	*shell = get_shell_data();
	if (!*shell)
		return (1);
	initialize_shlvl(&(*shell)->env);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell_data	*shell;
	char			*input;

	(void)ac;
	(void)av;
	(void)envp;
	if (initialize_shell(&shell))
		return (1);
	while (1)
	{
		input = get_input();
		if (!input)
			break ;
		if (ft_strlen(input) > 0)
		{
			handle_input(input, shell);
			g_exit_code = shell->last_exit_status;
		}
		else
			free(input);
	}
	free(input);
	rl_clear_history();
	ft_cleanup_shell(&shell);
	return (g_exit_code);
}
