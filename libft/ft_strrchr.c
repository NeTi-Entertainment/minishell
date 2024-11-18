/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:15:58 by caubert           #+#    #+#             */
/*   Updated: 2024/05/23 10:30:53 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*n;

	i = 0;
	n = NULL;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			n = ((char *)&str[i]);
		}
		i++;
	}
	if (str[i] == (char)c)
	{
		n = ((char *)&str[i]);
	}
	return (n);
}
