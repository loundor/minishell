/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:42 by stissera          #+#    #+#             */
/*   Updated: 2022/08/29 15:10:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cd(char *rep, char *path, char *old)
{
	free(rep);
	free(path);
	free(old);
}

int	cd(t_shell *shell)
{
	char	*rep;
	char	*path;
	char	*old;

	rep = NULL;
	old = getcwd((void *)0, 0);
	path = search_var("HOME");
	if (!shell->cmd->param || shell->cmd->param == NULL)
	{
		if (path != NULL)
			chdir(path);
	}
	else
	{
		if (shell->cmd->param[0] == '~' && (shell->cmd->param[1] == '/'
				|| shell->cmd->param[1] == 0) && path != NULL)
		{
			rep = ft_strjoin(path, &shell->cmd->param[1]);
			chdir(rep);
		}
		else if (shell->cmd->param[0] != '~' || shell->cmd->param[1] != 0)
			chdir(shell->cmd->param);
	}
	set_env(shell->env, old, "OLDPWD");
	free_cd(rep, path, old);
	path = getcwd((void *)0, 0);
	set_env(shell->env, path, "PWD");
	free(path);
	return (ft_errmsg(errno));
}
