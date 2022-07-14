NAME		= 	minishell
CC			= 	gcc
FLAGS		= 	-Wall -Werror -Wextra ${EXTRAF}
EXTRAF		= 	-g
LIBRARY		= 	#-Llibft -lreadline -L./lib/libft # -L./readline/lib -I./readline/include
INCLUDES	= 	-I./includes/  #-I./lib/libft -I./readline/include
#BUILTIN		=	echo.c \
				cd .c
SRCS		= 	main.c \
				ft_error.c \
				env_pars.c \
				welcome.c #\
				${addprefix /builtin/, ${BUILTIN}}

OBJS		= 	$(addprefix ./srcs/, ${SRCS: .c=.o})
RM			= 	rm -rf

$(NAME)		:	${OBJS}
				${CC} ${FLAGS} ${LIBRARY} ${INCLUDES} ${OBJS} ./lib/libft/libft.a -o $@

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