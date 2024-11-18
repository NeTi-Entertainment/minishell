/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:33:27 by caubert           #+#    #+#             */
/*   Updated: 2024/05/28 13:45:30 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (0);
	d = dest;
	s = src;
	if (d <= s || d >= (s + size))
	{
		while (size--)
			*d++ = *s++;
	}
	else
	{
		d += size;
		s += size;
		while (size--)
		{
			*--d = *--s;
		}
	}
	return (dest);
}
