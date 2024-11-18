/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:20:39 by caubert           #+#    #+#             */
/*   Updated: 2024/10/04 15:35:24 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_env_string(const char *key, const char *value)
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

static char	**allocate_env_array(t_env *env, int *count)
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

static int	fill_env_array(char **env_array, t_env *env)
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
