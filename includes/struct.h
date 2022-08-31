/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:30:18 by stissera          #+#    #+#             */
/*   Updated: 2022/08/31 22:44:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
/*	Leave that in moment....								*/
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
}	t_cmd;

typedef struct s_tree
{
	int				type;
	uint8_t			code_err;
	struct s_cmd	*cmdr;
	struct s_pipe	*pipe[2];
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_shell
{
	char				*line;
	uint8_t				return_err;
	struct s_env		*env;
	struct s_tree		*tree;
	struct s_builtins	*builtin;
	struct sigaction	signal_act;
}	t_shell;

#endif