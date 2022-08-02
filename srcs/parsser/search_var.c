/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:21:33 by stissera          #+#    #+#             */
/*   Updated: 2022/07/29 10:56:52 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -------------------| SEARCH $VAR |---------------------- */
/*	Search and return de value of asked variable			*/
/*	Check and compare the asked variable in env struct		*/
/*	When env->next is flase that s mark en of struct		*/
/*	Check if var as same of env->var, if same use ft_strdup */
/*	and return the right variable, otherwise return NULL	*/
/* -------------------------------------------------------- */

char	*search_var(char *var)
{
	t_env	*env;
	t_env	*tmp;
	char	*line;

	env = (t_env *)struct_passing(2, NULL);
	tmp = env;
	while (ft_strcmp(var, tmp->env_var[0]) && tmp->next_env != NULL)
		tmp = tmp->next_env;
	if (!ft_strcmp(var, tmp->env_var[0]))
		line = ft_strdup(tmp->env_var[1]);
	else
		return (NULL);
	return (line);
}
