/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress_pf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:42:38 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:03:05 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar_static(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_addresslen(unsigned long nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		i++;
		nb /= 16;
	}
	return (i);
}

static void	ft_writeaddress(unsigned long nb, char format)
{
	if (nb >= 16)
	{
		ft_writeaddress(nb / 16, format);
		ft_writeaddress(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_static((nb + '0'), 1);
		else
			ft_putchar_static((nb - 10 + 'a'), 1);
	}
}

int	ft_putaddress_pf(unsigned long nb, char format)
{
	if (nb == 0)
		return (write(1, "(nil)", 5));
	else
	{
		write(1, "0x", 2);
		ft_writeaddress(nb, format);
	}
	return (ft_addresslen(nb) + 2);
}
