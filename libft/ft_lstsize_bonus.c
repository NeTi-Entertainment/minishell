/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:16:13 by caubert           #+#    #+#             */
/*   Updated: 2024/05/29 12:58:38 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	if (!lst)
		return (0);
	count = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
