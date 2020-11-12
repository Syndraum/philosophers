# SRCDIR = ./src
OBJDIR = ./objects
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

D_INCLUDE	= ./includes
INCLUDE	= $(addprefix ${INCDIR}/, header.h)

CC		= clang
CFLAGS	= -g -Wall -Wextra -Werror -I$(INCDIR) -pthread

RN		= rm -f

NAME	= philo_one

all:	${NAME}

${OBJDIR}/%.o : ./%.c
	${CC} ${CFLAGS} -c -o $@ $<

make_o:
	@mkdir -p ${OBJDIR}

${NAME}: make_o ${OBJS} ${INCLUDE}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re