/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:42 by stissera          #+#    #+#             */
/*   Updated: 2022/09/20 20:00:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_home(char *param, char *path)
{
	char	*rep;

	rep = NULL;
	if (param[0] == '~'
		&& (param[1] == '/'
			|| param[1] == 0) && path != NULL)
	{
		rep = ft_strjoin(path, &param[1]);
		chdir(rep);
	}
	else if (param[0] != '~'
		|| param[1] != 0)
		chdir(param);
	free(rep);
}

int	cd(char **par)
{
	char	*param;
	char	*path;
	char	*old;
	t_shell	*shell;

	param = par[1];
	shell = struct_passing(1, 0);
	old = getcwd((void *)0, 0);
	path = search_var("HOME");
	if (!param || param == NULL)
	{
		if (path != NULL)
			chdir(path);
	}
	else
		write_home(param, path);
	set_env(shell->env, old, "OLDPWD");
	free(path);
	free(old);
	path = getcwd((void *)0, 0);
	set_env(shell->env, path, "PWD");
	free(path);
	return (errno % 256);
}
