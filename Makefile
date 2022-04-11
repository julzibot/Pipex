# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jibot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:19:15 by jibot             #+#    #+#              #
#    Updated: 2022/04/11 16:59:13 by jibot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

CC		= gcc -Wall -Wextra -Werror

RM		= rm -f

SRCS	= Pipex.c Pipex_utils.c Split.c

OBJS	= ${SRCS:.c=.o}

all:		${NAME}

%.o:	%.c
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${OBJS} -o ${NAME}
			
clean: 
			${RM} ${SRCS:.c=.o}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
