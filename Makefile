SRC= philo.c \
	 errors.c \
	 ft_state.c \

OBJ= ${SRC:%.c=%.o}

CFLAGS= -Wall -Wextra -Werror -pthread
CC = cc


NAME = philo

all : ${NAME}

${NAME}: ${OBJ} philo.h
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	rm -rf  ${NAME}  ${OBJ}

