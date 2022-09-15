NAME		= 	minishell
CC			= 	gcc
FLAGS		= 	-Wall -Werror -Wextra ${EXTRAF}
EXTRAF		= 	-g -fsanitize=address
# MACOS - Fonctionne uniquement sur ma session42
LIBRARY		=  -lreadline -Lreadline/lib -L./lib/libft ./lib/libft/libft.a
INCLUDES	= 	-I./includes -I./readline -I./lib/libft 
# LINUX
#LIBRARY		=   ./readline.linux/shlib/libreadline.a ./readline.linux/shlib/libhistory.a -lncurses -L./readline.linux/shlib -L./lib/libft ./lib/libft/libft.a
#INCLUDES	= 	-I./includes -I./lib/libft
SRCS		= 	add_env.c \
				add_env_2.c \
				builtins.c \
				env_pars.c \
				free.c \
				main.c \
				prompt.c \
				signal.c \
				welcome.c \
				test.c \
				${addprefix builtins/, ${BUILTIN}} \
				${addprefix parsser/, ${PARSER}} \
				${addprefix utils/, ${UTILS}} \
				${addprefix tree/, ${TREE}}
BUILTIN		=	cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c
PARSER		=	dollar.c \
				double_quotes.c \
				exec.c \
				line.c \
				line_2.c \
				param.c \
				path.c \
				pre_parse.c \
				search_var.c \
				single_quote.c \
				wildcard.c 
TREE		=	bt_create_node_2.c \
				bt_create_node.c \
				bt_create.c \
				bt_test_sep_2.c \
				bt_test_sep.c \
				bt_write_cmd.c
UTILS		=	env_to_exec.c \
				errmsg.c \
				execute.c \
				get.c \
				ifstar.c \
				param_to_exec.c \
				search_in_path.c
#execute.c 		
			
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
