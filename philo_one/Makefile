SRCS	=	main.c \
			str.c \
			conv.c \
			mem.c

OBJS	= ${SRCS:.c=.o}

INCLUDE	= $(addprefix ${D_INCLUDE}/, header.h)
D_INCLUDE	= includes

CC		= clang
CFLAGS	= -g -Wall -Wextra -Werror -I $(D_INCLUDE) -pthread

RN		= rm -f

NAME	= philo_one

all:	${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re