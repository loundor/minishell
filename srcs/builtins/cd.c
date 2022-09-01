/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:42 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 10:19:32 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_home(t_shell *shell, char *path)
{
	char	*rep;

	rep = NULL;
	if (shell->tree->cmdr->param[0] == '~'
		&& (shell->tree->cmdr->param[1] == '/'
			|| shell->tree->cmdr->param[1] == 0) && path != NULL)
	{
		rep = ft_strjoin(path, &shell->tree->cmdr->param[1]);
		chdir(rep);
	}
	else if (shell->tree->cmdr->param[0] != '~'
		|| shell->tree->cmdr->param[1] != 0)
		chdir(shell->tree->cmdr->param);
	free(rep);
}

int	cd(t_shell *shell)
{
	char	*path;
	char	*old;

	old = getcwd((void *)0, 0);
	path = search_var("HOME");
	if (!shell->tree->cmdr->param
		|| shell->tree->cmdr->param == NULL)
	{
		if (path != NULL)
			chdir(path);
	}
	else
		write_home(shell, path);
	set_env(shell->env, old, "OLDPWD");
	free(path);
	free(old);
	path = getcwd((void *)0, 0);
	set_env(shell->env, path, "PWD");
	free(path);
	return (ft_errmsg(errno));
}
