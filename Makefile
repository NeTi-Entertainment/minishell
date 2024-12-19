# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caubert <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/04 15:09:04 by caubert           #+#    #+#              #
#    Updated: 2024/10/04 15:28:17 by caubert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-g -Wall -Werror -Wextra -I./include -I./libft

SRC_DIR		=	src

OBJ_DIR		=	obj

LIBFT_DIR	=	libft

SRCS		=	$(shell find $(SRC_DIR) -name '*.c')

OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT		=	$(LIBFT_DIR)/libft.a

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean:			clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re:				fclean all

.PHONY:			all clean fclean re
