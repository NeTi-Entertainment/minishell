/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 08:39:08 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:17:09 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_gnl(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}

char	*ft_strchr_gnl(const char *read_buffer, int c)
{
	if (!read_buffer)
		return (NULL);
	while (*read_buffer)
	{
		if (*read_buffer == (char)c)
			return ((char *)read_buffer);
		read_buffer++;
	}
	if (*read_buffer == (char)c)
		return ((char *)read_buffer);
	else
		return (NULL);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *src)
{
	size_t	length;
	char	*dest;

	length = ft_strlen_gnl(src);
	dest = (char *)malloc((length + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	return (ft_strcpy_gnl(dest, src));
}

char	*ft_strjoin_gnl(char *read_buffer, const char *read_content)
{
	size_t	buf_size;
	size_t	cont_size;
	char	*new_buf;
	char	*src;
	char	*new_buf_ptr;

	buf_size = 0;
	if (!read_buffer && !read_content)
		return (NULL);
	if (read_buffer)
		buf_size = ft_strlen_gnl(read_buffer);
	cont_size = ft_strlen_gnl(read_content);
	new_buf = (char *)malloc((buf_size + cont_size + 1) * sizeof(char));
	if (!new_buf)
		return (NULL);
	new_buf_ptr = new_buf;
	src = read_buffer;
	while (src && *src)
		*new_buf_ptr++ = *src++;
	src = (char *)read_content;
	while (src && *src)
		*new_buf_ptr++ = *src++;
	*new_buf_ptr = '\0';
	free(read_buffer);
	return (new_buf);
}
