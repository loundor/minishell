/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:09:04 by stissera          #+#    #+#             */
/*   Updated: 2022/07/11 22:19:47 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READLINE_LIBRARY
//# include "../lib/libft/libft.h"
//# include "../lib/libft/gnl/gnl.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <sys/wait.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>

# define STDIN	0
# define STDOUT	1
# define STDERR 2

# define FILE_HISTORY ".minishell_history"

/* ****************** */
/*	  ERROR MESSAGE   */
/* ****************** */
# define ACCESS_ERR "Access denied!"
# define INVALID_CMD "Command not found!"
# define WELCOME_ERR "Welcome error"

typedef struct s_commande
{
	char	*command;
}	t_cmd;

int		ft_echo(int flags, char *str); // echo prg
int		cd(char *directory); // change directory
int		pwd(void); // write the working directory
int		export(char *str); // set a env variable
int		unset(char *var); // unset a env variable
int		parser(char *str); // split the commande
int		check_auth(char **path, char *dest);	// check the access
void	msg_err(char *errno);	// Write the descripted error
// Welcome msg return 0 if ok, otherwise number of type error
int		welcome(void);
char	*take_simple_quote(char *str);
char	*take_double_quote(char *str);
int		w_history(char **history); // write history
void	create_command(char **argv, char **env);

#endif
