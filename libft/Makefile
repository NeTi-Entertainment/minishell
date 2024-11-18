# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caubert <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 11:10:08 by caubert           #+#    #+#              #
#    Updated: 2024/10/25 13:45:04 by caubert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=		cc

CFLAGS	=		-Wall -Wextra -Werror

NAME	=		libft.a

AR		=		ar rcs

SOURCES =		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		  		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		  		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		  		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
		  		ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		  		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		  		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
				ft_printf.c ft_putaddress_pf.c ft_putchar_pf.c ft_puthex_pf.c \
				ft_putnbr_pf.c ft_putstr_pf.c ft_putunsigned_pf.c \
				get_next_line.c get_next_line_utils.c ft_power.c ft_calloc_mt.c \
				ft_putstr_mt.c ft_strlen_mt.c ft_strcmp.c ft_strcat.c ft_realloc.c \
				ft_strncpy.c ft_isspace.c ft_strtok.c ft_strcpy.c ft_strndup.c \
				ft_strnew.c ft_realloc_bis.c ft_atol.c ft_is_valid_identifier.c

SOURCES_B =		ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
				ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJECTS	=		$(SOURCES:.c=.o)

OBJECTS_B =		$(SOURCES_B:.c=.o)

%.o:			%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

bonus:			$(OBJECTS_B)
	$(AR) $(NAME) $(OBJECTS_B)

clean:			
	rm -f $(OBJECTS) $(OBJECTS_B)

fclean:			clean	
	rm -f $(NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re
