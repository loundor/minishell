NAME		= 	minishell
CC			= 	gcc
FLAGS		= 	-Wall -Werror -Wextra ${EXTRAF}
EXTRAF		= 	-g -fsanitize=address
LIBRARY		=  -lreadline -Lreadline/lib #-Llibft -L./lib/libft
INCLUDES	= 	-I./includes -I./readline -I./lib/libft 
#LIBRARY		=  -lreadline #-Lreadline/lib #-Llibft -L./lib/libft
#INCLUDES	= 	-I./includes #-I./readline/include/readline #-I./lib/libft 
SRCS		= 	builtins.c \
				cmd_parse.c \
				env_pars.c \
				free.c \
				ft_error.c \
				main.c \
				param_parse.c \
				prompt.c \
				signal.c \
				welcome.c \
				test.c \
				${addprefix builtins/, ${BUILTIN}}
BUILTIN		=	cd.c \
				env.c \
				pwd.c
OBJS		= 	$(addprefix ./srcs/, ${SRCS: .c=.o})
RM			= 	rm -rf

#.c.o		:
#				$(CC) $(FLAGS) $(INCLUDES) -c $< -o ${<:.c=.o}

$(NAME)		:	${OBJS}
				${CC} ${FLAGS} ${INCLUDES} ${LIBRARY} ${OBJS} ./lib/libft/libft.a -o $@

all			:	${NAME}

#re			:	fclean all

clean		:
				${RM} ${OBJS}

#fclean		:	clean
#				${RED} ${RM} ${NAME} ${RST}	

.PHONY		:	${NAME} all clean fclean re

# Color
RED			= echo '\033[0;31m';
BLUE		= echo '\03[0;34m';
GREEN		= echo '\033[0;32m';
WHITE		= echo '\033[0;37m';
RST			= echo '\033[0m';
