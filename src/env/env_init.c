/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:56:21 by caubert           #+#    #+#             */
/*   Updated: 2024/11/28 18:56:21 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**allocate_env_array(t_env *env, int *count)
{
	char	**env_array;
	t_env	*current;

	*count = 0;
	current = env;
	while (current)
	{
		(*count)++;
		current = current->next;
	}
	env_array = malloc(sizeof(char *) * (*count + 1));
	return (env_array);
}

int	fill_env_array(char **env_array, t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current)
	{
		env_array[i] = create_env_string(current->key, current->value);
		if (!env_array[i])
			return (0);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (1);
}

t_env	*create_env_node(char *env_str)
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

void	add_env_node(t_env **env_list, t_env *new_node)
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

t_env	*init_env(char **envp)
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
