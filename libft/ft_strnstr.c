/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:36:07 by caubert           #+#    #+#             */
/*   Updated: 2024/05/24 12:50:12 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t l)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (lit[0] == '\0')
		return ((char *)big);
	while (i < l && big[i])
	{
		j = 0;
		while (i + j < l && big[i + j] && lit[j] && big[i + j] == lit[j])
		{
			j++;
		}
		if (lit[j] == '\0')
		{
			return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
