/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:16 by caubert           #+#    #+#             */
/*   Updated: 2024/09/20 14:18:24 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int i, size_t count)
{
	unsigned char	*str;

	str = (unsigned char *)ptr;
	while (count--)
		*str++ = (unsigned char)i;
	return (ptr);
}
