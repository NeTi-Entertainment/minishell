/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:38:38 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:06:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_pf(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		ft_putstr_pf("-2147483648");
		return (11);
	}
	else
	{
		if (nb < 0)
		{
			ft_putchar_pf('-');
			count++;
			nb *= -1;
		}
		if (nb > 9)
			count += ft_putnbr_pf(nb / 10);
		ft_putchar_pf((nb % 10) + '0');
		count++;
	}
	return (count);
}
