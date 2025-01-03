/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:56:04 by caubert           #+#    #+#             */
/*   Updated: 2025/01/02 13:23:28 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_env_string(const char *key, const char *value)
{
	int		len;
	char	*env_string;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	env_string = malloc(sizeof(char) * len);
	if (!env_string)
		return (NULL);
	ft_strcpy(env_string, key);
	ft_strcat(env_string, "=");
	ft_strcat(env_string, value);
	return (env_string);
}

void	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_env;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = *env;
	*env = new_env;
}

void	remove_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	**env_list_to_array(t_env *env)
{
	int		count;
	char	**env_array;
	int		i;

	env_array = allocate_env_array(env, &count);
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, env))
	{
		i = 0;
		while (env_array[i])
			free(env_array[i++]);
		free(env_array);
		return (NULL);
	}
	return (env_array);
}
