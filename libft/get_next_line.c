/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 08:31:12 by caubert           #+#    #+#             */
/*   Updated: 2024/06/26 11:16:56 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_break_gnl(char *read_buffer, size_t i)
{
	char	*ptr;

	ptr = read_buffer + i;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	return (ptr - read_buffer);
}

static char	*ft_line_read_gnl(char *read_buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!read_buffer || *read_buffer == '\0')
		return (NULL);
	i = ft_find_break_gnl(read_buffer, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (*(read_buffer + i) && *(read_buffer + i) != '\n')
	{
		*(line + i) = *(read_buffer + i);
		i++;
	}
	if (*(read_buffer + i) == '\n')
	{
		*(line + i) = *(read_buffer + i);
		i++;
	}
	*(line + i) = '\0';
	return (line);
}

static char	*ft_substr_gnl(char *read_buffer)
{
	char	*new_buf;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*read_buffer || !read_buffer)
		return (free(read_buffer), NULL);
	i = ft_find_break_gnl(read_buffer, i);
	new_buf = (char *)malloc ((ft_strlen_gnl(read_buffer) - i) + 1);
	if (!new_buf)
		return (free(new_buf), NULL);
	while (*(read_buffer + i))
		*(new_buf + j++) = *(read_buffer + i++);
	*(new_buf + j) = '\0';
	if (!*new_buf)
		return (free(read_buffer), free(new_buf), NULL);
	free(read_buffer);
	return (new_buf);
}

static char	*ft_free_gnl(char *read_content, char *read_buffer)
{
	free(read_content);
	free(read_buffer);
	read_buffer = NULL;
	return (read_buffer);
}

char	*get_next_line(int fd)
{
	char		*read_content;
	int			read_bytes;
	static char	*read_buffer;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	read_content = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_content)
		return (NULL);
	while (!(ft_strchr_gnl(read_buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, read_content, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			read_buffer = ft_free_gnl(read_content, read_buffer);
			return (NULL);
		}
		*(read_content + read_bytes) = '\0';
		read_buffer = ft_strjoin_gnl(read_buffer, read_content);
	}
	free(read_content);
	read_content = ft_line_read_gnl(read_buffer);
	read_buffer = ft_substr_gnl(read_buffer);
	return (read_content);
}
