/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:41:57 by stissera          #+#    #+#             */
/*   Updated: 2022/07/21 19:38:23 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -------------------| DO THE BUILTIN |------------------- */
/*	Add builtins in a structure with a pointer of function	*/
/*	NEED ALWAYS CREATE A TEMPORARY TO PUT shell->builtin	*/
/*				DO NO MOVE THE FIRST OCCURENCE				*/
/*					OF BUILTIN STRUC IN SHELL				*/
/*				THE STRUCT IN ONLY A SIMPLE LIST			*/
/*				(HAVE ONLY A NEXT NO PREVIOUS!) 			*/
/* -------------------------------------------------------- */
static void	init_builtins(char *cmd, int (*f)(), t_shell *sh)
{
	t_builtins	*builtins;
	t_builtins	*tmp;

	builtins = (t_builtins *) malloc(sizeof(t_builtins));
	if (!builtins)
		ft_exit(MALLOCERR, 1);
	builtins->cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!builtins->cmd)
		ft_exit(MALLOCERR, 2);
	ft_strlcpy(builtins->cmd, cmd, ft_strlen(cmd) + 1);
	builtins->f = f;
	if (sh->builtin)
	{
		tmp = sh->builtin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = builtins;
	}
	else
		sh->builtin = builtins;
}

/* -------------| INITIALISATION OF BUILTIN |-------------- */
/*	Call the function init_builtins to place the ptr of the	*/
/*	function in structure builtins							*/
/*	Can add a builtins easyer!!								*/
/* -------------------------------------------------------- */
int	add_builtins(t_shell *shell)
{
	init_builtins("pwd", &pwd, shell);
	init_builtins("env", &env, shell);
	init_builtins("cd", &cd, shell);
	init_builtins("test", &test, shell); // builtin for new test.
	return (0);
}

/* ------------------| SEARCH BUILTIN |-------------------- */
/*	Check the struct builtin to found the cmd, if the		*/
/*	command exist we return the pointer of the builtin		*/
/*	otherwise NULL.											*/
/* -------------------------------------------------------- */
t_builtins	*search_builtin(char *cmd, t_builtins *builtin)
{
	t_builtins	*tmp;

	tmp = builtin;
	while (ft_strlen(cmd) != ft_strlen(tmp->cmd)
		|| ft_strncmp(cmd, tmp->cmd, ft_strlen(tmp->cmd))
		|| ft_strncmp(cmd, tmp->cmd, ft_strlen(cmd)))
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			return (NULL);
	}
	return (tmp);
}
