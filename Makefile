SRC= philo.c \
	 errors.c \
	 ft_state.c \
	 utils.c \

OBJ= ${SRC:%.c=%.o}

CFLAGS= -Wall -Wextra -Werror -pthread -g
CC = cc


NAME = philo

all : ${NAME}

${NAME}: ${OBJ} philo.h
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	rm -rf  ${NAME}  ${OBJ}

re : clean all