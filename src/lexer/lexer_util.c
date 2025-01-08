/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:18:14 by caubert           #+#    #+#             */
/*   Updated: 2025/01/08 11:18:14 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_token_failed(t_ta *ta)
{
	free(ta->tokens);
	free(ta->quoted);
	ta->tokens = NULL;
	ta->quoted = NULL;
	return (1);
}
