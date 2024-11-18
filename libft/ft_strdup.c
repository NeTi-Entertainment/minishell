/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:12:19 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 16:04:39 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = ft_strnew(ft_strlen(src));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}
