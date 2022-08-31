/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:26:15 by stissera          #+#    #+#             */
/*   Updated: 2022/08/31 16:05:07 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -------------| ENVIRONNEMENT VARIABLES  |--------------- */
/*	Parse all env in a struct t_env							*/
/*	Struct : env_var	[0] NAME OF VARIALBLE				*/
/*						[1] VARIABLES						*/
/*	Can add variable with export very easy					*/
/*	Need to put all variable in a **char the execve			*/
/* -------------------------------------------------------- */

static t_env	*first(char **env)
{
	t_env	*tenv;

	tenv = (t_env *)malloc(sizeof(t_env));
	if (!tenv)
		exit(ft_exit(MALLOCERR, 1));
	tenv->prev_env = NULL;
	tenv->env_var = ft_split(*env, '=');
	tenv->next_env = NULL;
	return (tenv);
}

t_env	*do_env(char **env)
{
	t_env	*tenv;
	t_env	*ret;
	t_env	*parsse;

	if (*env != NULL)
	{
		tenv = first(env);
		ret = tenv;
	}
	while (++env && *env)
	{
		parsse = 0;
		parsse = (t_env *)malloc(sizeof(t_env));
		if (!parsse)
			exit(ft_exit(MALLOCERR, 1));
		parsse->prev_env = tenv;
		parsse->env_var = ft_split(*env, '=');
		parsse->next_env = NULL;
		tenv->next_env = parsse;
		tenv = tenv->next_env;
	}
	return (ret);
}
