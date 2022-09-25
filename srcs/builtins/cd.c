/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:42 by stissera          #+#    #+#             */
/*   Updated: 2022/09/24 14:08:56 by stissera         ###   ########.fr       */
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
	if ((!param || param == NULL) && path != NULL)
		chdir(path);
	else if (param || param != NULL)
		write_home(param, path);
	set_env(shell->env, old, "OLDPWD");
	free(path);
	path = getcwd((void *)0, 0);
	set_env(shell->env, path, "PWD");
	if (errno != 0)
	{
		printf("minishell: cd: %s: no file or directory!\n", param);
		return (1 + free_str(path) + free_str(old));
	}
	return (0 + free_str(path) + free_str(old));
}
