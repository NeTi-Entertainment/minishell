/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:46:02 by caubert           #+#    #+#             */
/*   Updated: 2024/12/10 14:46:02 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*del = delimiter, i_fd = input_fd*/
static int	handle_heredoc_child(int *pipes, const char *del, int exp, int i_fd)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	close(pipes[0]);
	if (dup2(i_fd, STDIN_FILENO) == -1)
		exit(1);
	if (read_minimal_heredoc(pipes[1], del, exp) != 0)
		exit(1);
	close(pipes[1]);
	cleanup_heredoc_process();
	exit(0);
}

static int	setup_heredoc_fds(int *pipes, int *tty_fd, int *stdin_backup)
{
	*tty_fd = open("/dev/tty", O_RDONLY);
	*stdin_backup = dup(STDIN_FILENO);
	if (*tty_fd == -1 || pipe(pipes) == -1)
	{
		if (*stdin_backup != -1)
			close(*stdin_backup);
		return (0);
	}
	return (1);
}

static void	update_shell_data(int pipe_read_fd, int stdin_backup)
{
	t_shell_data	*shell;

	shell = get_shell_data();
	shell->cmd->has_heredoc = 1;
	shell->cmd->heredoc_fd = pipe_read_fd;
	shell->cmd->tty_backup = stdin_backup;
}

static int	handle_heredoc_fork(int *pipes, char *del, int exp, int tty_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		handle_heredoc_child(pipes, del, exp, tty_fd);
	close(pipes[1]);
	close(tty_fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(pipes[0]);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (-1);
	return (0);
}

int	handle_heredoc(char *delimiter, int eof_quoted)
{
	int		pipes[2];
	int		result;
	int		tty_fd;
	int		stdin_backup;

	if (!validate_delimiter(delimiter))
		return (-1);
	if (!setup_heredoc_fds(pipes, &tty_fd, &stdin_backup))
		return (-1);
	result = handle_heredoc_fork(pipes, delimiter, !eof_quoted, tty_fd);
	if (result == -1)
	{
		close(stdin_backup);
		return (cleanup_heredoc_pipes(pipes));
	}
	update_shell_data(pipes[0], stdin_backup);
	return (setup_heredoc_input(pipes[0]));
}
