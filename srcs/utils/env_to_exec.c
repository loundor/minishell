/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:42:20 by stissera          #+#    #+#             */
/*   Updated: 2022/09/08 20:27:33 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ---------------| STRUCT ENV TO CHAR **  |--------------- */
/*  Take struct env and put put the all in char ** malloced */
/*  Don't forget to free the returned value!!               */
/* -------------------------------------------------------- */

static char	**env_to_exec_send(int i, t_env *env)
{
	char	*tmp;
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * (++i + 1));
	if (!ret)
		exit(ft_exit(errno, 1));
	ret[i] = NULL;
	while (--i >= 0)
	{
		tmp = ft_strjoin(env->env_var[0], "=");
		ret[i] = ft_strjoin(tmp, env->env_var[1]) + free_str(tmp);
//		free (tmp);
		env = env->prev_env;
	}
	return (ret);
}

char	**env_to_exec(void)
{
	t_env	*env;
	int		i;

	env = (t_env *)struct_passing(2, 0);
	i = 0;
	while (env != NULL && env->next_env != NULL)
	{
		env = env->next_env;
		i++;
	}
	if (i == 0)
		return (NULL);
	return (env_to_exec_send(i, env));
}
