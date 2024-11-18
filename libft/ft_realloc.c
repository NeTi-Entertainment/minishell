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

void	*ft_realloc(void *ptr, size_t newsize)
{
	void	*newptr;
	size_t	oldsize;

	if (ptr == NULL)
	{
		newptr = malloc(newsize);
		if (newptr != NULL)
			ft_memset(newptr, 0, newsize);
		return (newptr);
	}
	oldsize = malloc_usable_size(ptr);
	if (newsize < oldsize)
		oldsize = newsize;
	newptr = malloc(newsize);
	if (newptr == NULL)
		return (NULL);
	ft_memset(newptr, 0, newsize);
	ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}
