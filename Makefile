# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jibot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:19:15 by jibot             #+#    #+#              #
#    Updated: 2022/03/25 17:41:36 by jibot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

CC		= gcc -Wall -Wextra -Werror

RM		= rm -f

SRCS	= Pipex.c 

OBJS	= ${SRCS:.c=.o}

all:		${NAME}

%.o:	%.c
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			make all -C ./libft
			${CC} -o ${NAME} ${OBJS} libft/libft.a
			
clean: 
			${RM} ${SRCS:.c=.o}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus_re:	fclean bonus

.PHONY:		all clean fclean re
