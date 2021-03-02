OBJDIR = objects
INCDIR = ./includes

SRCS	=	main.c \
			str.c \
			conv.c \
			mem.c \
			is.c \
			init.c \
			timestamp.c \
			print.c \
			list.c \
			free.c

OBJS	= $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})
INCLUDE	= $(addprefix ${INCDIR}/, header.h)

CC		= clang
CFLAGS	= -g -Wall -Wextra -Werror -I$(INCDIR) -pthread

RM		= rm -f

NAME	= philo_one

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