/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:09:04 by stissera          #+#    #+#             */
/*   Updated: 2022/07/17 16:57:24 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READLINE_LIBRARY
# include "../lib/libft/libft.h"
//# include "../lib/libft/gnl/gnl.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
//# include "../readline-8.0/readline.h"
//# include "../readline-8.0/history.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define STDIN	0
# define STDOUT	1
# define STDERR 2

# define FILE_HISTORY ".minishell_history"

/* ****************** */
/*	  ERROR MESSAGE   */
/* ****************** */
# define ACCESS_ERR "Access denied!"
# define INVALID_CMD "Command not found!"

typedef enum e_typeerror
{
	ALLRIGHT,
	ENV,
	MALLOCERR,
	WELCOME_ERR,
	NO_ENV,
	SIGN
}	t_error;

typedef struct s_env
{
	struct s_env	*prev_env;
	char			**env_var;
	struct s_env	*next_env;
}	t_env;

typedef struct s_cmd
{
	char			*command;
	char			*param;
	char			*option;
	int				type; // 0-none; 1-|; 2-||; 3-&& ; 4->; 5->>; 6-<; 7-<<
	int				fd;
	struct s_pipe	*pipe[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char				*line;
	pid_t				*pid;
	struct s_env		*env;
	struct s_cmd		*cmd;
	struct sigaction	signal_act;
}	t_shell;

/* ************ */
/*   PROGRAM    */
/* ************ */

int		pwd(t_shell *shell); // write the working directory

int		ft_echo(char *str); // echo prg
int		cd(char *directory); // change directory
int		export(char *str); // set a env variable
int		unset(char *var); // unset a env variable

/* ************ */
/*   INTERN     */
/* ************ */
// Welcome msg return 0 if ok, otherwise number of type error
int		welcome(void);
int		w_history(char **history); // write history
int		parser(char *str); // split the commande
void	create_command(char **argv, char **env);

/* ************ */
/*     SUB      */
/* ************ */

t_env	*do_env(char **env); // Parssing from env ok - check return error
int		ft_exit(int type, int to_free, void *data); // Need complet with right error and right free()
int		prompt(t_shell *shell);

char	*take_simple_quote(char *str);
char	*take_double_quote(char *str);
int		check_auth(char **path, char *dest);	// check the access

#endif
