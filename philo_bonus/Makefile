# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 18:29:22 by mbouyahy          #+#    #+#              #
#    Updated: 2023/04/08 23:04:14 by mbouyahy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = utiles.c time_functions.c create_philosophers.c check_argv.c main.c

OBJS =	${SRCS:.c=.o}

NAME =	philo_bonus

RM =	rm -f

CC =	cc

FLAGS =	-Wall -Wextra -Werror

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} philo_bonus.h
		 ${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean bonus re