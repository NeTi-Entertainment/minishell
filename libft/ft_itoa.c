/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:22:00 by caubert           #+#    #+#             */
/*   Updated: 2024/05/24 15:43:07 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_length(int nb)
{
	int	len;

	len = 0;
	if (nb < 1)
		len++;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static long long	ft_absolute(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

static char	*ft_newstr(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				sign;
	int				len;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_length(n);
	str = ft_newstr(len);
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	nb = ft_absolute(n);
	while (len--)
	{
		*(str + len) = '0' + nb % 10;
		nb /= 10;
	}
	if (sign)
		*(str) = '-';
	return (str);
}
