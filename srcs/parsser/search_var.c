/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:21:33 by stissera          #+#    #+#             */
/*   Updated: 2022/09/08 21:19:26 by stissera         ###   ########.fr       */
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
	t_shell	*shell;
	char	*line;

	if (*var == '?')
	{
		shell = (t_shell *)struct_passing(1, NULL);
		return (ft_itoa((int)shell->return_err));
	}
	env = (t_env *)struct_passing(2, NULL);
	tmp = env;
	while (tmp && tmp->next_env != NULL && ft_strcmp(var, tmp->env_var[0]))
		tmp = tmp->next_env;
	if (tmp && tmp->env_var[1] != NULL && !ft_strcmp(var, tmp->env_var[0]))
		line = ft_strdup(tmp->env_var[1]);
	else
		return (NULL);
	return (line);
}
