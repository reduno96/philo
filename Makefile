SRC= philo.c \
	 ft_state.c \
	 utils.c \
	 ft_create_threads.c \
	 ft_all_mutex.c \
	 ft_main.c \
	 ft_initialize.c \

OBJ= ${SRC:%.c=%.o}

CFLAGS= -Wall -Wextra -Werror -pthread
CC = cc


NAME = philo

all : ${NAME}

${NAME}: ${OBJ} philo.h
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	rm -rf ${OBJ}

fclean : clean
	rm -rf ${NAME}

re : clean all