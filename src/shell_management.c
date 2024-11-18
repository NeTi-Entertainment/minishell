/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:35 by caubert           #+#    #+#             */
/*   Updated: 2024/10/08 14:58:10 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*equals_sign;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equals_sign = ft_strchr(env_str, '=');
	if (!equals_sign)
	{
		free(node);
		return (NULL);
	}
	node->key = ft_strndup(env_str, equals_sign - env_str);
	node->value = ft_strdup(equals_sign + 1);
	node->next = NULL;
	return (node);
}

static void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*env_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_node = create_env_node(envp[i]);
		if (env_node)
			add_env_node(&env_list, env_node);
		i++;
	}
	return (env_list);
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
