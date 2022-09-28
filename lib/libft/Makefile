NAME	= libft.a
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
FOLDER	= ./srcs
FLAGS	= -Wall -Wextra -Werror
SRCS	=	ft_atoi.c ft_memchr.c ft_split.c \
			ft_strnstr.c ft_bzero.c ft_memcmp.c \
			ft_strchr.c ft_strrchr.c ft_calloc.c \
			ft_memcpy.c ft_strdup.c ft_strtrim.c \
			ft_isalnum.c ft_memmove.c ft_strjoin.c \
			ft_substr.c ft_isalpha.c ft_memset.c \
			ft_strlcat.c ft_tolower.c ft_isascii.c \
			ft_putchar_fd.c ft_strlcpy.c ft_toupper.c \
			ft_isdigit.c ft_putendl_fd.c ft_strlen.c \
			ft_isprint.c ft_putnbr_fd.c ft_strmapi.c \
			ft_striteri.c ft_itoa.c ft_putstr_fd.c \
			ft_strncmp.c ft_skipspace.c ft_isspace.c \
			ft_joincts.c ft_strcmp.c ft_cnttab.c ft_tabbzero.c \
			get_next_line.c
OBJS	= $(addprefix ./, ${SRCS:.c=.o})
BONUSSRCS = 
BNS		= $(addprefix ./, ${BONUSSRCS:.c=.o})
HEADER =	./libft.h ./gnl/get_next_line.c

.c.o		:
			${CC} ${FLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

all		: ${NAME}

clean	:
			rm -f ${OBJS} ${BNS}

fclean	:	clean
			rm -f ${NAME}

re		:	fclean all

$(NAME)	:	${OBJS}
			ar -rcs ${NAME} ${OBJS}

bonus	:	${BNS} ${OBJS}
			ar -rcs ${NAME} ${BNS} ${OBJS}

.PHONY	:	all clean fclean re ${NAME}
