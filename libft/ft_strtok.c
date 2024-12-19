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

static void	clean_original(char **original)
{
	if (*original)
	{
		free(*original);
		*original = NULL;
	}
}

static char	*reset_stock(char **original, char **stock)
{
	clean_original(original);
	*stock = NULL;
	return (NULL);
}

static char	*process_token(char **stock, char sepa)
{
	char	*ptr;

	ptr = NULL;
	while (**stock == sepa)
		(*stock)++;
	if (**stock != '\0')
	{
		ptr = *stock;
		while (**stock && **stock != sepa)
			(*stock)++;
		if (**stock != '\0')
		{
			**stock = '\0';
			(*stock)++;
		}
	}
	return (ptr);
}

char	*ft_strtok(char *str, char sepa)
{
	static char	*stock;
	static char	*original;

	if (str != NULL)
	{
		clean_original(&original);
		stock = ft_strdup(str);
		original = stock;
	}
	if (!stock || *stock == '\0')
		return (reset_stock(&original, &stock));
	return (process_token(&stock, sepa));
}
