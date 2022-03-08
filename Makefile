NAME	=	philo

SRCS	=	libft.c \
			main.c \
			preparing.c \
			threads.c

OBJS	=	$(SRCS:%.c=%.o)

CC 		=	gcc

RM		=	rm -f

FLAGS 	=	-Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS} philo.h
			${CC} ${FLAGS} -o ${NAME} ${OBJS} -lpthread

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re