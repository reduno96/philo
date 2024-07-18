SRC= philo.c \
	 errors.c \
	 ft_state.c \
	 utils.c \
	 ft_create_threads.c \
	 ft_all_mutex.c \

OBJ= ${SRC:%.c=%.o}

# CFLAGS= -Wall -Wextra -Werror -pthread -fsanitize=thread -g
CFLAGS= -Wall -Wextra -Werror -pthread  -g
CC = cc


NAME = philo

all : ${NAME}

${NAME}: ${OBJ} philo.h
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	rm -rf  ${NAME}  ${OBJ}

re : clean all