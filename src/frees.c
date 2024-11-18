/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:10:19 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 15:41:33 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_tokenarray(t_ta *ta)
{
	int	i;

	if (!ta)
		return ;
	if (ta->tokens)
	{
		i = 0;
		while (i < ta->count)
		{
//			printf("freeing token[%d]: %s\n", i, ta->tokens[i]);
			if (ta->tokens[i])
				free(ta->tokens[i]);
			i++;
		}
//		printf("freeing tokens array\n");
		free(ta->tokens);
	}
	if (ta->quoted)
	{
//		printf("freeing quoted array\n");
		free(ta->quoted);
	}
	if (ta->token)
	{
//		printf("freeing token temp\n");
		free(ta->token);
	}
//	printf("freeing structure itself\n");
	free(ta);
}

void	free_redirects(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		free(redirect->file);
		free(redirect);
		redirect = temp;
	}
}

void	free_command(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (!cmd)
		return ;
//	printf("freeing command at %p\n", cmd);
//	for (int j = 0; j < cmd->arg_count; j++)
//	{
//		printf("freeing argument[%d] att %p: %s\n", j, cmd->args[j], cmd->args[j]);
//	}
	current = cmd;
	while (current)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->args)
		{
			i = 0;
			while (i < current->arg_count)
			{
				if (current->args[i])
					free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		if (current->redirects)
			free_redirects(current->redirects);
		if (current->fd_info)
			free(current->fd_info);
//		printf("freeing cmd itself at %p\n", cmd);
		free(current);
		current = next;
	}
}

void	ft_cleanup_shell(t_shell_data **shell)
{
	t_env	*current;
	t_env	*next;

	if (!shell || !*shell)
		return ;
	current = (*shell)->env;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	if ((*shell)->cmd)
		free_command((*shell)->cmd);
	free(*shell);
	*shell = NULL;
}

void	ft_cleanup_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}
