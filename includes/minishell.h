/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:09:04 by stissera          #+#    #+#             */
/*   Updated: 2022/08/30 17:48:34 by stissera         ###   ########.fr       */
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
# include "./struct.h"
# define STDIN	0
# define STDOUT	1
# define STDERR 2

/* ---------------------| BUILTINS |----------------------- */
/*															*/
/* -------------------------------------------------------- */
t_builtins	*search_builtin(char *cmd, t_builtins *builtin); // OK
int			add_builtins(t_shell *shell); // OK
int			cd(t_shell *shell); // ok change directory
int			pwd(void); // ok
int			env(t_shell *shell); // ok
int			ft_echo(t_shell *shell); // ok echo builtins
int			export(t_shell *shell); // ok set a env variable

/* -----------------------| UTILS |------------------------ */
/*															*/
/* -------------------------------------------------------- */
int			welcome(void); // OK
t_env		*do_env(char **env); // ok
int			ft_errmsg(int errn); // ok Print error message
int			get_cmd_type(char *line); // ok
t_cmd		*cmd_parse(char *shell, t_shell *cmd);
void		*struct_passing(int type, void *data); // ok
char		**env_to_exec(void); // ok Parsse struc env to char **
int			prepare_exe(t_shell *shell);
int			core(t_shell *shell);// ACTUALY ONLY FOR TEST

/* --------------------| FREE PARTY |---------------------- */
/*															*/
/* -------------------------------------------------------- */
int			ft_exit(int type, int to_free); // Need complet
void		free_builtins(t_builtins *builtins);
void		free_cmd(t_cmd *cmd);
void		free_env(t_env *env);
void		free_shell(t_shell *shell);
int			prompt(t_shell *shell);

// TREE
t_tree		*bt_create(char *line); // ok
int			bt_test_and(char *line); // ok
int			bt_test_or(char *line); // ok
int			bt_test_pipe(char *line); // ok
int			bt_test_redir(char *line); // ok
int			bt_test_appd(char *line); // ok
int			bt_test_input(char *line); // ok
int			bt_test_heredoc(char *line);
char		*parse_space(char *line);
void		free_bt(t_tree *tree);

// ENVIRONEMENT VARIABLES
void		add_env_line(char *line); // ok
void		add_env_splited(t_env *env, char *str, char *type); // ok
void		set_env(t_env *env, char *str, char *type); // ok
void		rem_env(t_env *env, char *str); // ok
int			unset(t_shell *shell); // ok unset a env variable

// PARSSING
char		*line_parse(char *cmd);
char		*take_dollar(char *param); // ok
char		*take_single_quote(char *param);
char		*take_double_quote(char *param);
char		*take_path(char *line, t_cmd *cmd);
char		*take_exec(char *line, t_cmd *cmd);
char		*take_params(char *line, t_cmd *cmd);
char		*search_var(char *var); // ok
int			starcmp(t_wildcard	*test); // ok

// SYSTEM
int			prep_signal(t_shell *shell);

/* ************ */
/*     SUB      */
/* ************ */
int			test(void *data);
#endif

// char		*take_operator(char *line, t_cmd *cmd);