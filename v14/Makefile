# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 17:02:12 by mjafari           #+#    #+#              #
#    Updated: 2022/08/01 16:59:53 by mjafari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC		= main.c parser.c pipe_splitter.c redirection.c redirection_utils.c\
		heredoc_input.c dollar_with_q.c dollar_no_q.c\
		cmd_c.c ./builtins/*.c exe_cmd.c init.c utils.c

FLAG	= -lreadline

CC		= gcc

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

remove:
	rm -f mini_temp*

rename:
	mv mini_temp_pipe_after mini_temp_pipe_after