S_SRC = main.c  split.c  utils.c  env_bs.c
D_SRC = ./src/
SRC = $(addprefix ${D_SRC}, ${S_SRC})

S_OBJ = ${S_SRC:.c=.o}
D_OBJ = ./obj/
OBJ = $(addprefix ${D_OBJ}, ${S_OBJ})

S_INC = pipex.h
D_INC = ./inc/
INC = $(addprefix ${D_INC}, ${S_INC})


NAME = pipex

CC = cc

FLAGS = -Wall -Wextra -Werror -g

${D_OBJ}%.o : ${D_SRC}%.c ${INC}
	${CC} ${FLAGS} -I${D_INC} -c $< -o $@

all	: ${NAME}

${NAME}	:	${D_OBJ}  ${OBJ}
	${CC} ${FLAGS} ${OBJ} ${LIBFT}-o${NAME}

${D_OBJ}:
	mkdir -p ${D_OBJ}

clean :
	rm -f ${OBJ}

fclean :
	rm -f ${NAME} ${OBJ}

re : fclean all

.PHONY : all clean fclean re
