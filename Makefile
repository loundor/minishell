NAME		= 	minishell
CC			= 	gcc
FLAGS		= 	-Wall -Werror -Wextra ${EXTRAF}
EXTRAF		= 	-g -fsanitize=address
# MACOS - Fonctionne uniquement sur ma session42
#LIBRARY		=  -lreadline -Lreadline/lib -L./lib/libft ./lib/libft/libft.a
#INCLUDES	= 	-I./includes -I./readline -I./lib/libft 
# LINUX
LIBRARY		=   ./readline.linux/shlib/libreadline.a ./readline.linux/shlib/libhistory.a -lncurses -L./readline.linux/shlib -L./lib/libft ./lib/libft/libft.a
INCLUDES	= 	-I./includes -I./lib/libft
SRCS		= 	add_env.c \
				builtins.c \
				cmd_parse.c \
				env_pars.c \
				free.c \
				main.c \
				prompt.c \
				signal.c \
				welcome.c \
				test.c \
				tree/bt_create.c \
				tree/bt_test_sep.c \
				parsser/dollar.c \
				parsser/double_quotes.c \
				parsser/exec.c \
				parsser/line.c \
				parsser/param.c \
				parsser/path.c \
				parsser/pre_parse.c \
				parsser/search_var.c \
				parsser/single_quote.c \
				parsser/wildcard.c \
				utils/env_to_exec.c \
				utils/get.c \
				utils/errmsg.c \
				${addprefix builtins/, ${BUILTIN}}
BUILTIN		=	cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c
OBJS		= 	$(addprefix ./srcs/, ${SRCS: .c=.o})
RM			= 	rm -rf

#.c.o		:
#				$(CC) $(FLAGS) $(INCLUDES) -c $< -o ${<:.c=.o}

$(NAME)		:	${OBJS}
				${CC} ${FLAGS} ${OBJS} ${INCLUDES} ${LIBRARY} -o $@

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
