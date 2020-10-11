SRCS	= main.c
OBJS	= ${SRCS:.c=.o}

INCLUDE	= $(addprefix ${D_INCLUDE}/, header.h)
D_INCLUDE	= includes

CC		= clang-9
CFLAGS	= -Wall -Wextra -Werror -I $(D_INCLUDE)

RN		= rm -f

NAME	= philo_one

all:	${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	${CC} ${CFLAG} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re