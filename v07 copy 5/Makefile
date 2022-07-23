# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 17:02:12 by mjafari           #+#    #+#              #
#    Updated: 2022/07/22 20:51:24 by mjafari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC		= main.c parser.c lexer.c dollar.c redirection.c

FLAG	= -lreadline

CC		= clang

SRC_OBJ	= $(SRC:.c=.o)

LIBPATH	= ./libft

LIBRARY	= libft.a

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	make bonus -C $(LIBPATH)

$(NAME):
	$(CC) $(FLAG) -g -o $(NAME) $(SRC) -L $(LIBPATH) -lft

clean:
	make clean -C $(LIBPATH)
	rm -f $(SRC_OBJ)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -f $(NAME)

re: fclean all