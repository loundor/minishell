/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:26:15 by stissera          #+#    #+#             */
/*   Updated: 2022/07/13 14:39:57 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*do_env(char **env)
{
	t_env	*tenv;
	t_env	*ret;
	t_env	*parsse;

	if (*env)
	{
		tenv = malloc(sizeof(t_env));
		if (!tenv)
			exit(ft_error(MALLOCERR));
		tenv->env_var = ft_split(*env, '=');
		ret = tenv;
	}
	while (++env && *env)
	{
		parsse = 0;
		parsse = malloc(sizeof(t_env));
		if (!parsse)
			exit(ft_free_lvl(1));
		parsse->prev_env = tenv;
		parsse->env_var = ft_split(*env, '=');
		tenv->next_env = parsse;
		tenv = tenv->next_env;
	}
	ret = parse_path(tenv, ret);
	return (ret);
}

static t_env	*parse_path(t_env *tenv, t_env *ret)
{
	tenv->next_env = ret;
	ret->prev_env = tenv;
	return (ret);
}
