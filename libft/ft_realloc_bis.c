/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:10:00 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 17:19:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc_bis(void *ptr, size_t newsize)
{
	void	*newptr;
	size_t	cursize;

	if (ptr == NULL)
	{
		newptr = malloc(newsize);
		if (newptr)
			ft_memset(newptr, 0, newsize);
		return (newptr);
	}
	cursize = ft_strlen(ptr);
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memset(newptr, 0, newsize);
	ft_memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}
