/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:26:15 by stissera          #+#    #+#             */
/*   Updated: 2022/07/13 16:22:20 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*parse_path(t_env *tenv, t_env *ret)
{
	char	**path;
	t_env	*cmp;

	tenv->next_env = ret;
	ret->prev_env = tenv;
	cmp = ret;
	while (ft_strncmp(cmp->env_var[0], "PATH", 4) != 0)
		cmp = cmp->next_env;
	path = ft_split(ft_strjoin("PATH:", cmp->env_var[1]), ':');
	free(cmp->env_var);
	cmp->env_var = path;
	return (ret);
}

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
