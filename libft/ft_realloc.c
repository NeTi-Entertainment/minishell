/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:20:20 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 17:30:29 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*realloc_new_allocation(size_t newsize)
{
	void	*newptr;

	newptr = malloc(newsize);
	if (newptr)
		ft_memset(newptr, 0, newsize);
	return (newptr);
}

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	void	*newptr;
	size_t	copysize;

	if (!ptr)
		return (realloc_new_allocation(newsize));
	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	copysize = oldsize;
	if (newsize < oldsize)
		copysize = newsize;
	ft_memcpy(newptr, ptr, copysize);
	if (newsize > oldsize)
		ft_memset((char *)newptr + oldsize, 0, newsize - oldsize);
	free(ptr);
	return (newptr);
}
