/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:56:36 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 14:26:32 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	update_exit_status(t_shell_data *shell_data)
{
	if (g_sig == SIGINT)
		shell_data->last_exit_status = 130;
	g_sig = 0;
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	sigint_handler(int sig)
{
	g_sig = sig;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putchar_fd('\n', 1);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
