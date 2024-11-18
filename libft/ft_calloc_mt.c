/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_mt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:45:11 by caubert           #+#    #+#             */
/*   Updated: 2024/07/04 12:46:52 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_mt(size_t count, size_t size)
{
	size_t	total;
	void	*ret;

	total = size * count;
	ret = malloc(total);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_bzero(ret, total);
	return (ret);
}
