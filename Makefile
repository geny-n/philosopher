# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 18:24:58 by ngeny             #+#    #+#              #
#    Updated: 2025/01/16 17:11:14 by ngeny            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

GREEN = \033[0;32m
WHITE=\033[0m

OBJDIR = ./OBJ/
CC = cc
FLAGS = -Wall -Wextra -Werror -g


MAINSRC = 	main.c \
			init.c \
			philo_life.c \
			dead_or_alive.c \
			utils.c \
			free.c \

SOURCES = ${MAINSRC}
OBJ = ${SOURCES:%.c=${OBJDIR}%.o}

all : ${NAME}

${NAME} : ${OBJ} ${LIBFT}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}
	@echo "${GREEN}*************  Compilation success  *************${WHITE}"

${OBJDIR}%.o : ${SRC}%.c
	mkdir -p ${dir $@}
	${CC} ${FLAGS} -c -o $@ $<

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY :
	all clean fclean re