/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 18:11:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	struct_passing(0, &shell);
	shell.env = NULL;
	do_env(env);
	shell.line = NULL;
	shell.return_err = 0;
	shell.history = 0;
	shell.builtin = NULL;
	shell.tree = NULL;
	shell.h_list = NULL;
	if (!shell.env)
		exit(ft_exit(ENV, 0));
	if (argc == 1)
		(void)argv;
	if (add_builtins(&shell) || welcome() || ft_set_history(&shell)
		|| prompt(&shell) || ft_write_history(&shell))
		exit(ft_exit(errno, 1));
	ft_exit(0, 1);
	write(1, "\001\033[0m\002exit\n\0", 11);
	return (0);
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

	if (reload != 1)
	{
		shell = (t_shell *)data;
		reload = 1;
		return (0);
	}
	if (type == 1)
		return (shell);
	else if (type == 2)
		return ((t_env *)shell->env);
	else if (type == 3)
		return ((t_cmd *)shell->tree->cmdr);
	else if (type == 4)
		return ((t_builtins *)shell->builtin);
	else if (type == 5)
		return ((t_tree *)shell->tree);
	return (0);
}
