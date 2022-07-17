NAME		= 	minishell
CC			= 	gcc
FLAGS		= 	-Wall -Werror -Wextra ${EXTRAF}
EXTRAF		= 	-g
LIBRARY		=  -lreadline -Lreadline/shlib #-Llibft -L./lib/libft
INCLUDES	= 	-I./includes -I./readline #-I./lib/libft 
#LIBRARY		=  -lreadline #-Lreadline/lib #-Llibft -L./lib/libft
#INCLUDES	= 	-I./includes #-I./readline/include/readline #-I./lib/libft 
#BUILTIN		=	echo.c \
				cd .c
SRCS		= 	main.c \
				ft_error.c \
				env_pars.c \
				welcome.c \
				prompt.c #\
				${addprefix /builtin/, ${BUILTIN}}

OBJS		= 	$(addprefix ./srcs/, ${SRCS: .c=.o})
RM			= 	rm -rf

#.c.o		:
#				$(CC) $(FLAGS) $(INCLUDES) -c $< -o ${<:.c=.o}

$(NAME)		:	${OBJS}
				${CC} ${FLAGS} ${INCLUDES} ${LIBRARY} ${OBJS} ./lib/libft/libft.a -o $@

all			:	${NAME}

re			:	fclean all

clean		:
				${RM} ${OBJS}

fclean		:	clean
				${RED} ${RM} ${NAME} ${RST}	

.PHONY		:	${NAME} all clean fclean re

# Color
RED			= echo '\033[0;31m';
BLUE		= echo '\03[0;34m';
GREEN		= echo '\033[0;32m';
WHITE		= echo '\033[0;37m';
RST			= echo '\033[0m';
