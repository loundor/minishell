NAME		= minishell
CC			= gcc
FLAGS		= -Wall -Error -Wextra ${EXTRAF}
EXTRAF		= -g
LIBRARY		= -lreadline -L./readline/lib -I./readline/include
INCLUDES	= -I./includes/ 
SRCS		= main.c
OBJS		= $(addprefix ./srcs/, &{SRCS: .c=.o})
RM			= @rm -rf

$(NAME)		:	${OBJS}
				${CC} ${FLAGS} ${LIBRARY} ${INCLUDES} ${OBJS} -o $@

all			:	${NAME}

re			:	fclean all

clean		:
				${RM} ${OBJS}

fclean		:	clean
				${RED} ${RM} ${NAME} ${RST}	

.PHONY		:	${NAME} all clean fclean re

# Color
RED			= '\033[0;31m'
BLUE		= '\033[0;34m'
GREEN		= '\033[0;32m'
WHITE		= '\033[0;37m'
RST			= '\033[0m'