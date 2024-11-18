/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:58:12 by caubert           #+#    #+#             */
/*   Updated: 2024/10/23 17:51:50 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char sepa)
{
	static char	*stock;
	static char	*original;
	char		*ptr;

	ptr = NULL;
	if (str != NULL)
	{
		if (original)
		{
			free(original);
			original = NULL;
		}
		stock = ft_strdup(str);
		original = stock;
	}
	if (!stock || *stock == '\0')
	{
		if (original)
		{
			free(original);
			original = NULL;
		}
		stock = NULL;
		return (NULL);
	}
	while (*stock == sepa)
		stock++;
	if (*stock != '\0')
	{
		ptr = stock;
		while (*stock && *stock != sepa)
			stock++;
		if (*stock != '\0')
		{
			*stock = '\0';
			stock++;
		}
	}
	return (ptr);
}
