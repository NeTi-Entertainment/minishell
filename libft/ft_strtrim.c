/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:14:50 by caubert           #+#    #+#             */
/*   Updated: 2024/05/27 10:33:15 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		trim;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_is_set(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= i && ft_is_set(s1[j], set))
		j--;
	trim = j - i + 1;
	result = (char *)malloc(trim + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[i], trim + 1);
	return (result);
}
