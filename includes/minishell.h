/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:09:04 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 14:43:01 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READLINE_LIBRARY
# include "../lib/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
# include "../readline.linux/readline.h"
# include "../readline.linux/history.h"
//# include <readline/readline.h>
//# include <readline/history.h>
# include <errno.h>

# define STDIN	0
# define STDOUT	1
# define STDERR 2

typedef enum e_typeerror
{
	EXIT,
	ENV,
	MALLOCERR,
	WELCOME_ERR,
	NO_ENV,
	SIGN,
	BUILT,
	CMDNFOUND,
	ALLRIGHT
}	t_error;

/* -------------| ENVIRONNEMENT VARIABLES  |--------------- */
/*	Binary tree, need "type" for the type of separator		*/
/*	About type:	0 - end		1 - |	2 - ||	3- &&	4- >	*/
/*				5 - >>		6 - <	7 - <<					*/
/*	The code_err it the number returned by the programm.	*/
/*	The cmd take the path, name of file and param			*/
/*	for the no leaf, dont forget to put at NULL all			*/
/*	variable that we don't use!								*/
/* -------------------------------------------------------- */

typedef struct s_tree
{
	int				type;
	int				code_err;
	char			*cmd;
	struct t_cmd	*cmdr;
	struct s_pipe	*pipe[2];
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_builtins
{
	char				*cmd;
	int					(*f)();
	struct s_builtins	*next;
}	t_builtins;

typedef struct s_wildcard
{
	char		*str;
	int			ss;
	int			se;
	char		*pattern;
	int			ps;
	int			pe;
}	t_wildcard;

/* -------------| ENVIRONNEMENT VARIABLES  |--------------- */
/*	Maybe for somethings but i don't remember why...		*/
/*	A leave that in moment....								*/
/* -------------------------------------------------------- */

typedef struct s_pparams
{
	char				*line;
	char				*old;
}	t_pparams;

typedef struct s_env
{
	struct s_env	*prev_env;
	char			**env_var;
	struct s_env	*next_env;
}	t_env;

typedef struct s_tmp
{
	struct s_tmp		*prev;
	char				**var;
	struct s_tmp		*next;
}	t_tmp;

/* -------------| ENVIRONNEMENT VARIABLES  |--------------- */
/*	Variable command means the file							*/
/*	About type:	0 - end		1 - |	2 - ||	3- &&	4- >	*/
/*				5 - >>		6 - <	7 - <<					*/
/*		 ATTENTION au ' et " <--- Ne sais plus pkoi!!		*/
/*	Profondeur des perenthensis								*/
/* -------------------------------------------------------- */

typedef struct s_cmd
{
	char			*path;
	char			*command;
	char			*param;
	int				type;
	int				fd;
	int				result;
	int				parenthesis;
	struct s_pipe	*pipe[2];
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_shell
{
	char				*line;
	short unsigned int	*return_err;
	struct s_env		*env;
	struct s_cmd		*cmd;
	struct s_tree		*tree;
	struct s_builtins	*builtin;
	struct sigaction	signal_act;
}	t_shell;

// OK - NEED TEST
int			welcome(void); // OK
int			pwd(void); // Should ok
int			env(t_shell *shell); // Should ok
t_env		*do_env(char **env); // Parssing from env ok - check return error
t_builtins	*search_builtin(char *cmd, t_builtins *builtin); // OK
int			add_builtins(t_shell *shell); // OK
void		*struct_passing(int type, void *data);
t_cmd		*cmd_parse(char *shell, t_cmd *cmd);
int			ft_errmsg(int errn);

/* --------------------| FREE PARTY |---------------------- */
/*															*/
/* -------------------------------------------------------- */
int			ft_exit(int type, int to_free); // Need complet
void		free_builtins(t_builtins *builtins);
void		free_cmd(t_cmd *cmd);
void		free_env(t_env *env);
void		free_shell(t_shell *shell);
int			prompt(t_shell *shell);
int			get_cmd_type(char *line);

// TREE
t_tree		*bt_create(char *line);
int			bt_test_and(char *line);
int			bt_test_or(char *line);
int			bt_test_pipe(char *line);
int			bt_test_redir(char *line);
int			bt_test_appd(char *line);
int			bt_test_input(char *line);
int			bt_test_heredoc(char *line);
char		*parse_space(char *line);
void		free_bt(t_tree *tree);

// ENVIRONEMENT VARIABLES
void		add_env_line(char *line);
void		set_env(t_env *env, char *str, char* type);
void		add_env_splited(t_env *env, char *str, char* type);
void		rem_env(t_env *env, char *str);
int			unset(t_shell *shell); // unset a env variable
int			export(t_shell *shell); // set a env variable

//		-- PARSSING
char		*line_parse(char *cmd);
char		*take_dollar(char *param);
char		*take_single_quote(char *param);
char		*take_double_quote(char *param);
char		*take_path(char *line, t_cmd *cmd);
char		*take_exec(char *line, t_cmd *cmd);
char		*take_params(char *line, t_cmd *cmd);
char		*take_operator(char *line, t_cmd *cmd);
char		*search_var(char *var);
int			starcmp(t_wildcard	*test);

char		**env_to_exec(void); // Parsse struc env to char **
int			prepare_exe(t_shell *shell);
int			cd(t_shell *shell); // change directory
int			core(t_shell *shell);// ACTUALY ONLY FOR TEST
int			prep_signal(t_shell *shell);

// TO DO
int			ft_echo(char *str); // echo prg
int			parser(char *str); // split the commande
void		create_command(char **argv, char **env);
int			w_history(char **history); // write history

int			check_auth(char **path, char *dest);	// check the access
int			see_errno(t_env *env);

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
int			test(void *data);
#endif
