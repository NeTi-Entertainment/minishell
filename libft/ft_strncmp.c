/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:35:40 by caubert           #+#    #+#             */
/*   Updated: 2024/05/24 13:19:06 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t l)
{
	if (l == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && l > 1)
	{
		s1++;
		s2++;
		l--;
	}
	return (((unsigned char)(*s1) - (unsigned char)(*s2)));
}
