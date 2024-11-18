/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:39:55 by caubert           #+#    #+#             */
/*   Updated: 2024/05/30 16:00:34 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(*(tab + i));
	}
	free(tab);
}

static size_t	ft_word_count(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count ++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (count);
}

static size_t	my_strlen(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static char	**my_split(char const *s, char c, char **tab, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(tab + i) = ft_substr(s, j, my_strlen(&*(s + j), c));
		if (!*(tab + i))
		{
			ft_free(tab, i);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(tab + i) = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_word_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab = my_split(s, c, tab, count);
	return (tab);
}
