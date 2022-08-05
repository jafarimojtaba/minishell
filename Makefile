# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 17:02:12 by mjafari           #+#    #+#              #
#    Updated: 2022/08/05 22:16:42 by mjafari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC		= ./builtins/*.c *.c

FLAG	= -Wall -Werror -Wextra -lreadline

CC		= clang

SRC_OBJ	= $(SRC:.c=.o)

LIBPATH	= ./libft

LIBRARY	= libft.a

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	make -C $(LIBPATH)

$(NAME):
	$(CC) $(FLAG) -g -o $(NAME) $(SRC) -L $(LIBPATH) -lft

clean:
	make clean -C $(LIBPATH)
	rm -f $(SRC_OBJ)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -f $(NAME)

re: fclean all

remove:
	rm -f mini_temp*

rename:
	mv mini_temp_pipe_after mini_temp_pipe_after