/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:38:16 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:03:19 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar_static(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_hexlen(unsigned int nb)
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

static void	ft_writehex(unsigned int nb, char format)
{
	if (nb >= 16)
	{
		ft_writehex(nb / 16, format);
		ft_writehex(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_static((nb + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_static((nb - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_static((nb - 10 + 'A'), 1);
		}
	}
}

int	ft_puthex_pf(unsigned int nb, char format)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		ft_writehex(nb, format);
	return (ft_hexlen(nb));
}
