/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:48:53 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 13:44:47 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <malloc.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		is_valid_identifier(const char *str);

long	ft_atol(const char *str);

char	*ft_strnew(size_t size);

char	*ft_strndup(const char *s, size_t n);

int		ft_isspace(int c);

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize);

void	*ft_realloc_bis(void *ptr, size_t newsize);

char	*ft_strncpy(char *dest, char *src, unsigned int n);

char	*ft_strcat(char *dest, const char *src);

char	*ft_strcpy(char *dest, const char *src);

int		ft_strcmp(const char *s1, const char *s2);

int		ft_atoi(const char *str);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size);

void	*ft_calloc_mt(size_t count, size_t size);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *memblk, int c, size_t size);

int		ft_memcmp(const void *p1, const void *p2, size_t size);

void	*ft_memcpy(void *dest, const void *src, size_t size);

void	*ft_memmove(void *dest, const void *src, size_t size);

void	*ft_memset(void *ptr, int i, size_t count);

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *s, int fd);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *str, int c);

char	*ft_strdup(const char *src);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcat(char *dest, const char *src, size_t size);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

size_t	ft_strlen(const char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(const char *s1, const char *s2, size_t l);

char	*ft_strnstr(const char *big, const char *lit, size_t l);

char	*ft_strrchr(const char *str, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);

int		ft_toupper(int c);

int		ft_power(int nb, int power);

char	*ft_strtok(char *str, char sepa);

char	*ft_strstr(char *str, char *to_find);

/*for chained lists*/

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*printf and utils*/

int		ft_printf(const char *format, ...)\
__attribute__ ((format(printf, 1, 2)));

int		ft_putaddress_pf(unsigned long nb, char format);

int		ft_putchar_pf(char c);

int		ft_puthex_pf(unsigned int nb, char format);

int		ft_putnbr_pf(int nb);

int		ft_putstr_pf(char *str);

int		ft_putunsigned_pf(unsigned int nb);

/*get next line and utils*/

char	*get_next_line(int fd);

char	*ft_strchr_gnl(const char *read_buffer, int c);

size_t	ft_strlen_gnl(const char *str);

char	*ft_strjoin_gnl(char *read_buffer, const char *read_content);

char	*ft_strcpy_gnl(char *dest, const char *src);

char	*ft_strdup_gnl(const char *src);

/*minitalk and utils*/

void	ft_putstr_mt(char *str, int len, int fd);

size_t	ft_strlen_mt(const char *str);

#endif
