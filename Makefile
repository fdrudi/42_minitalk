# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 12:24:46 by fdrudi            #+#    #+#              #
#    Updated: 2022/03/09 12:24:46 by fdrudi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT	=	client

NAME_SERVER	=	server


SRC_CLIENT	=	client.c utils.c\

SRC_SERVER	=	server.c utils.c\


OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)


CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror


all:			$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):	$(OBJ_CLIENT)
				$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT)

$(NAME_SERVER):	$(OBJ_SERVER)
				$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER)


clean:
				$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)

fclean:			clean
				$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER)

re:				fclean all

.PHONY:		all clean fclean re
