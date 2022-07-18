/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:09:04 by stissera          #+#    #+#             */
/*   Updated: 2022/07/18 18:29:53 by stissera         ###   ########.fr       */
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
	int				type; // 0- end; 1- |; 2- ||; 3- && ; 4- >; 5- >>; 6- <; 7- << // ATTENTION au ' et "
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

// OK - NEED TEST
int		welcome(void); // OK
int		pwd(t_shell *shell); // Should ok
int		env(t_shell *shell); // Should ok
t_env	*do_env(char **env); // Parssing from env ok - check return error

// WORKING
int		cd(char *directory); // change directory
int		ft_exit(int type, int to_free, void *data); // Need complet with right error and right free()
int		core(t_shell *shell);// ACTUALY ONLY FOR TEST
int		prep_signal(t_shell *shell);
int		prompt(t_shell *shell);

// TO DO
int		ft_echo(char *str); // echo prg
int		export(char *str); // set a env variable
int		unset(char *var); // unset a env variable
int		parser(char *str); // split the commande
void	create_command(char **argv, char **env);
int		w_history(char **history); // write history
char	*take_simple_quote(char *str);
char	*take_double_quote(char *str);
int		check_auth(char **path, char *dest);	// check the access

/* ************ */
/*   PROGRAM    */
/* ************ */

/* ************ */
/*   INTERN     */
/* ************ */
// Welcome msg return 0 if ok, otherwise number of type error

/* ************ */
/*     SUB      */
/* ************ */

#endif
