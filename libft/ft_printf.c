/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:10:23 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:08:35 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchr_static(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

static int	ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_putchar_pf((va_arg(args, int))));
	else if (format == 's')
		return (ft_putstr_pf((va_arg(args, char *))));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_pf((va_arg(args, int))));
	else if (format == 'x' || format == 'X')
		return (ft_puthex_pf(va_arg(args, unsigned int), format));
	else if (format == 'p')
		return (ft_putaddress_pf(va_arg(args, unsigned long), format));
	else if (format == 'u')
		return (ft_putunsigned_pf(va_arg(args, unsigned int)));
	else if (format == '%')
		return (ft_putchar_pf('%'));
	else
		return (-1);
}

static int	ft_handle_format(va_list args, const char *format, int *i)
{
	int	length;

	length = 0;
	if (*(format + *i) == '%' && *(format + *i + 1))
	{
		if (ft_strchr_static("cspdiuxX%", *(format + *i + 1)))
		{
			length += ft_format(args, *(format + *i + 1));
			(*i)++;
		}
		else
			length += ft_putchar_pf('%');
	}
	else if (*(format + *i) == '%' && *(format + *i + 1) == '\0')
	{
	}
	else
		length += ft_putchar_pf(*(format + *i));
	return (length);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		length;
	int		i;

	i = 0;
	length = 0;
	va_start(args, format);
	if (format == NULL)
		return (-1);
	while (*(format + i))
	{
		length += ft_handle_format(args, format, &i);
		i++;
	}
	va_end(args);
	return (length);
}
