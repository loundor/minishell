/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:41:57 by stissera          #+#    #+#             */
/*   Updated: 2022/07/19 12:33:31 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*      Add builtins in a structure with a pointer of function      */
/*       NEED ALWAYS CREATE A TEMPORARY TO PUT shell->builtin       */
/*     DO NO MOVE THE FIRST OCCURENCE OF BUILTIN STRUC IN SHELL     */
/* THE STRUCT IN ONLY A SIMPLE LIST (HAVE ONLY A NEXT NO PREVIOUS!) */

static void	init_builtins(char *cmd, int (*f)(), t_shell *sh)
{
	t_builtins	*builtins;
	t_builtins	*tmp;

	builtins = (t_builtins *) malloc(sizeof(t_builtins));
	if (!builtins)
		ft_exit(MALLOCERR, 1, sh);
	builtins->cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!builtins->cmd)
		ft_exit(MALLOCERR, 2, sh);
	ft_strlcpy(builtins->cmd, cmd, ft_strlen(cmd));
	builtins->f = f;
	if (sh->builtin)
	{
		tmp = sh->builtin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = builtins;
	}
	else
		sh->builtin = builtins;
}

int	add_builtins(t_shell *shell)
{
	init_builtins("pwd", &pwd, shell);
	init_builtins("env", &env, shell);
	return (0);
}

t_builtins	*search_builtin(char *cmd, t_builtins *builtin)
{
	t_builtins	*tmp;

	tmp = builtin;
	while (tmp && !ft_strncmp(cmd, tmp->cmd, ft_strlen(tmp->cmd)))
		tmp = tmp->next;
	return (tmp);
}
