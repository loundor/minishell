/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/07/21 16:18:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = do_env(env);
	if (!shell.env)
		exit(ft_exit(ENV, 0));
	if (argc == 1)
		(void)argv;
//	if (prep_signal(&shell))
//		exit(ft_exit(SIGN, 0));
	if (add_builtins(&shell))
		exit(ft_exit(BUILT, 0));
	if (welcome() != 0)
		exit (ft_exit(WELCOME_ERR, 2));
	if (!prompt(&shell))
		return (0);
	return (ft_exit(WELCOME_ERR, 1));
}

/* -----------------| PARSSE THE DIRECTORY |--------------- */
/*	This function help to take the structure. Used to free	*/
/*	before exit the program.								*/
/*	This function create a static at the first call. The	*/
/*	next call the function return the struct was asked!		*/
/* -------------------------------------------------------- */
void	*struct_passing(int type, void *data)
{
	static int			reload;
	static t_shell		*shell;
	static t_env		*env;
	static t_cmd		*cmd;
	static t_builtins	*builtins;

	if (reload != 1)
	{
		shell = (t_shell *)data;
		env = (t_env *)((t_shell *)data)->env;
		cmd = (t_cmd *)((t_shell *)data)->cmd;
		builtins = (t_builtins *)((t_shell *)data)->builtin;
		reload = 1;
	}
	if (type == 1)
		return (shell);
	else if (type == 2)
		return (env);
	else if (type == 3)
		return (0);
	return (0);
}
