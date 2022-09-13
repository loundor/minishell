/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:09:04 by stissera          #+#    #+#             */
/*   Updated: 2022/09/13 17:16:35 by stissera         ###   ########.fr       */
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
# include <fcntl.h>
# include <term.h>
# include "../readline.linux/readline.h"
# include "../readline.linux/history.h"
//# include <readline/readline.h>
//# include <readline/history.h>
# include <errno.h>
# include "./struct.h"
# include "./tree.h"

# define STDIN	0
# define STDOUT	1
# define STDERR 2

/* ---------------------| BUILTINS |----------------------- */
/*															*/
/* -------------------------------------------------------- */
t_builtins	*search_builtin(char *cmd, t_builtins *builtin); // OK
int			add_builtins(t_shell *shell); // OK
int			cd(char **par); // ok change directory
int			pwd(void); // ok
int			env(char **par); // ok
int			ft_echo(char **av); // ok echo builtins
int			export(char **par); // ok set a env variable

/* -----------------------| UTILS |------------------------ */
/*															*/
/* -------------------------------------------------------- */
int			welcome(void); // OK
t_env		*do_env(char **env); // ok
int			ft_errmsg(int errn); // ok Print error message
int			get_cmd_type(char *line); // ok
void		*struct_passing(int type, void *data); // ok
char		**env_to_exec(void); // ok Parsse struc env to char **
int			core(t_shell *shell);// ACTUALY ONLY FOR TEST

/* --------------------| FREE PARTY |---------------------- */
/*															*/
/* -------------------------------------------------------- */
int			ft_exit(int type, int to_free); // Need complet
void		free_builtins(t_builtins *builtins);
int			free_cmd(t_cmd *cmd);
int			free_env(t_env *env);
int			free_shell(t_shell *shell);
int			free_tab(char **t);
int			free_str(char *str);
int			prompt(t_shell *shell);

// ENVIRONEMENT VARIABLES
void		add_env_line(char *line); // ok
void		add_env_splited(t_env *env, char *str, char *type); // ok
void		set_env(t_env *env, char *str, char *type); // ok
void		rem_env(t_env *env, char *str); // ok
int			unset(char **par); // ok unset a env variable

// PARSSING
char		*parse_space(char *line);
char		*line_parse(char *cmd);
char		*alloc(int *end, char **ret, char *line);
char		*dollar(char *tmp, char *line, char **ret);
char		*take_dollar(char *param); // ok
char		*take_single_quote(char *param);
char		*take_double_quote(char *param);
char		*take_path(char *line, t_cmd *cmd);
char		*take_exec(char *line, t_cmd *cmd);
char		*take_params(char *line, t_cmd *cmd);
char		*search_var(char *var); // ok
int			starcmp(t_wildcard	*test); // ok
char		*count_quotes(char *ret, size_t *i);

// EXEC
// int			prepare_exec(t_shell *shell, t_tree * tree);
int			prep_signal(t_shell *shell);
//void		do_exec(t_shell *shell, t_tree *tree);
int			pre_prepare_exec(t_shell *shell, t_tree *tree);
int			prepare_exec(t_shell *shell, t_tree *tree);
int			wait_process(t_tree *tree, t_shell *shell);
int			close_all_fd(t_tree *tree);
char		**param_to_exec(char *str, char *name);
char		*search_in_path(char *command, char *env);
/* ************ */
/*     SUB      */
/* ************ */
int			test(void *data);
#endif