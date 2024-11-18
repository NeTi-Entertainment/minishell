/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:12:27 by caubert           #+#    #+#             */
/*   Updated: 2024/06/27 15:39:28 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_pf(int nb, int *length)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*length) += 11;
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_pf('-', length);
		ft_putnbr_pf(nb * -1, length);
	}
	else
	{
		if (nb > 9)
			ft_putnbr_pf(nb / 10, length);
		ft_putchar_pf(nb % 10 + '0', length);
	}
}

void	ft_putaddress_pf(size_t ptr, int *length)
{
	char	str[25];
	int		i;
	char	*base;

	base = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	(*length) += 2;
	if (ptr == 0)
	{
		ft_putchar_pf('0', length);
		return ;
	}
	while (ptr)
	{
		str[i] = base[ptr % 16];
		ptr /= 16;
		i++;
	}
	while (i--)
		ft_putchar_pf(str[i], length);
}

void	ft_puthex_pf(unsigned int nb, char format, int *length)
{
	char	str[25];
	char	*base;
	int		i;

	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	if (nb == 0)
	{
		ft_putchar_pf('0', length);
		return ;
	}
	while (nb != 0)
	{
		str[i] = base[nb % 16];
		nb /= 16;
		i++;
	}
	while (i--)
		ft_putchar_pf(str[i], length);
}

void	ft_putunsigned_pf(unsigned int nb, int *length)
{
	if (nb >= 10)
		ft_putunsigned_pf(nb / 10, length);
	ft_putchar_pf(nb % 10 + '0', length);
}
