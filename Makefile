# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 17:38:23 by abollen           #+#    #+#              #
#    Updated: 2022/03/02 15:04:16 by abollen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#***** VARIABLES *****#

PROJECT = PHILO
NAME = ./philosophers
HEADER = includes/philosophers.h

FILES = action.c destroy.c init.c main.c parsing.c protect.c threads.c utils.c
OBJ = ${addprefix ${OBJ_DIR}/,${FILES:.c=.o}}

SRC_DIR = src
OBJ_DIR = obj

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes

#***** RULES *****#

all : ${OBJ_DIR} ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${HEADER}
	@${CFLAGS} -Iincludes -c $< -o $@
	@echo "\033[95m[${PROJECT}]\033[92m[BUILD]\033[97m $@."

$(NAME): ${OBJ_DIR} $(OBJ) Makefile
	@$(CC) ${CFLAGS} $(OBJ) -o $(NAME)
	@echo "\033[36m[${PROJECT}]\033[92m[BUILD] \033[0m${NAME}"

${OBJ_DIR}:
	@mkdir obj
	@echo "\033[36m[${PROJECT}]\033[92m[BUILD] \033[0m${OBJ_DIR} folder"
	
clean :
	@rm -rf ${OBJ_DIR}
	@echo "\033[36m[${PROJECT}]\033[93m[CLEAN] \033[0m${OBJ_DIR} folder"

fclean : clean
	@rm -rf ${NAME}
	@echo "\033[36m[${PROJECT}]\033[93m[CLEAN] \033[0m${NAME}"

re: fclean all

.PHONY : all clean fclean re