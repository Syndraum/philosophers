OBJDIR = objects
INCDIR = ./includes

SRCS	=	main.c \
			str.c \
			conv.c \
			mem.c \
			timestamp.c \
			print.c \
			init.c \
			is.c \
			free.c \
			list.c \
			error.c

OBJS	= $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})
INCLUDE	= $(addprefix ${INCDIR}/, header.h)

CC		= clang
CFLAGS	= -g -Wall -Wextra -Werror -I$(INCDIR) -pthread

RM		= rm -f

NAME	= philo_two

all:	${NAME}

${OBJDIR}/%.o : ./%.c
	${CC} ${CFLAGS} -c -o $@ $<

${OBJDIR}:
	mkdir -p ${OBJDIR}

${OBJS} : ${INCLUDE} | ${OBJDIR}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re