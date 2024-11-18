/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:07:39 by caubert           #+#    #+#             */
/*   Updated: 2024/06/27 15:06:29 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_pf(char c, int *length)
{
	write(1, &c, 1);
	(*length)++;
}

void	ft_putstr_pf(char *str, int *length)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*length) += 6;
		return ;
	}
	while (str[len])
		len++;
	write(1, str, len);
	(*length) += len;
}
