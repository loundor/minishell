# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/31 19:02:34 by alfux             #+#    #+#              #
#    Updated: 2022/10/11 16:19:24 by alfux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SPATH	=	src/

SRC		=	main.c ft_prompt.c ft_cd.c ft_strtdup.c ft_sfree.c ft_env.c		\
			ft_newpwd.c ft_errmsg.c ft_free.c ft_echo.c ft_cmdspl.c			\
			ft_root_parse.c ft_pwd.c ft_exit.c ft_isbuiltin.c ft_parse.c	\
			ft_execute.c ft_setvar.c ft_strtcat.c ft_strtlen.c ft_isvarin.c	\
			ft_export.c ft_unset.c	ft_strtdelone.c ft_addhis.c ft_savhis.c	\
			ft_errno.c ft_gethis.c ft_isntvar.c ft_isextern.c ft_newpro.c	\
			ft_pipmkr.c ft_substrt.c ft_strtlcpy.c ft_init_var.c ft_extsta.c\
			ft_setenv.c ft_killall.c ft_waitall.c ft_redio.c ft_stdio.c		\
			ft_sighdl.c ft_newpmt.c ft_sigmsg.c ft_istokn.c	ft_skppar.c 	\
			ft_skpqts.c	ft_skpspc.c ft_syntax_err.c ft_macro_exec.c 		\
			ft_exit_toggle.c ft_tknize.c ft_remout.c ft_setio.c ft_setint.c	\
			ft_wldprep.c ft_skptkn.c ft_search.c ft_match.c ft_isdir.c		\
			ft_exicmd.c ft_cdpath.c ft_remaff.c ft_expvar.c ft_remqts.c		\
			ft_cndcmp.c ft_cndstr.c ft_lexord.c								\

OPATH	=	obj/

OBJ		=	$(SRC:%.c=$(OPATH)%.o)

LPATH	=	libft/

LIBFT	=	libft.a

HPATH	=	hdr/

RIPATH	=	/opt/homebrew/opt/readline/include

RLPATH	=	/opt/homebrew/opt/readline/lib

HEADER	=	minishell.h

MACROS	=	flags_macros.h

OPTION	=	-Wall -Werror -Wextra -I$(LPATH) -I$(HPATH) -I$(RIPATH) -g

SIL		=	--no-print-directory

NAME	=	minishell

HISTORY	=	.$(NAME)_history

CC		=	gcc

$(NAME)				:	$(OPATH) $(OBJ) $(LPATH)$(LIBFT)
						@($(CC) $(OPTION) $(OBJ) $(LPATH)$(LIBFT) -o	\
						$@ -L$(RLPATH) -lreadline)
						@(echo "\033[32m$@ linked\033[0m")

$(OPATH)%.o			:	$(SPATH)%.c $(HPATH)$(HEADER) $(HPATH)$(MACROS)
						@($(CC) $(OPTION) -c $< -o $@)
						@(echo "\033[90m$@ compiled\033[0m")

$(OPATH)			:
						@(mkdir $@)
						@(echo "\033[90m$@ directory created\033[0m")

$(LPATH)$(LIBFT)	:
						@(cd $(LPATH) && $(MAKE) $(SIL) bonus clean)
						@(echo "\033[90m$(LIBFT) compiled\033[0m")

all					:	$(NAME)

clean				:
						@(cd $(LPATH) && $(MAKE) $(SIL) fclean)
						@(rm -rf $(OPATH))
						@(echo "\033[31mobject files removed\033[0m")

fclean				:	clean
						@(cd $(LPATH) && $(MAKE) $(SIL) fclean)
						@(rm -rf $(NAME) && cd && rm -rf $(HISTORY))
						@(echo "\033[31m$(NAME) removed\033[0m")

re					:	fclean all

.PHONY				:	all clean fclean re
