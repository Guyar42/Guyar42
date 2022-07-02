NAME = philo

SRCS = sources/action.c sources/utils.c philo.c sources/initialize.c sources/action_code_6.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f 

NORME = norminette

%.o: %.c Makefile philo.h
		${CC}  ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
		${CC} ${CFLAGS}$^ -o $@

norme:
		${NORME} ${LIBFT} ${SRCS} so_long.h

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re lib norme