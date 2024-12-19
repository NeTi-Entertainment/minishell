/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_command_exp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:21:17 by caubert           #+#    #+#             */
/*   Updated: 2024/11/30 02:21:17 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_single_quoted(const char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (cmd[0] == '\'' && cmd[ft_strlen(cmd) - 1] == '\'')
		return (1);
	return (0);
}

static int	is_double_quoted(const char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (cmd[0] == '"' && cmd[ft_strlen(cmd) - 1] == '"')
		return (1);
	return (0);
}

int	is_expanded_invalid_cmd(const char *name, int quoted)
{
	char	*env_var;
	char	*env_value;
	int		i;

	i = 0;
	if (!name)
		return (0);
	if (!quoted)
		return (0);
	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_' || name[i] == '$'))
		i++;
	env_var = ft_substr(name, 1, i - 1);
	if (!env_var)
		return (0);
	env_value = get_env_value(get_shell_data()->env, env_var);
	free(env_var);
	if (!env_value)
		return (1);
	if (!name[i])
		return (quoted);
	return (0);
}

void	handle_expanded_invalid_cmd(t_cmd *cmd, t_shell_data *sd)
{
	if (is_single_quoted(cmd->name))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name + 1, 2);
		ft_putendl_fd(": command not found", 2);
		sd->last_exit_status = 127;
		return ;
	}
	if (is_double_quoted(cmd->name))
	{
		ft_putendl_fd("minishell: : command not found", 2);
		sd->last_exit_status = 127;
		return ;
	}
	else
	{
		sd->last_exit_status = 0;
		return ;
	}
}
