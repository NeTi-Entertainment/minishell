/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_pf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:52:37 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:09:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putstr_static(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_pf("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

static int	ft_numlen(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static char	*ft_itoa_static(unsigned int nb)
{
	char	*tab;
	int		len;

	len = ft_numlen(nb);
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (0);
	tab[len] = '\0';
	while (nb)
	{
		tab[len - 1] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (tab);
}

int	ft_putunsigned_pf(unsigned int nb)
{
	size_t	i;
	char	*tab;

	i = 0;
	if (nb == 0)
		i = i + write(1, "0", 1);
	else
	{
		tab = ft_itoa_static(nb);
		i = i + ft_putstr_static(tab);
		free(tab);
	}
	return (i);
}
