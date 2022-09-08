/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:18:27 by stissera          #+#    #+#             */
/*   Updated: 2022/09/08 21:15:30 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ----------------| WRITE THE ENV VAR |------------------- */
/*	Just take the struct env and print all line separed by =*/
/*	index 0 = VAR NAME						index 1 = VALUE	*/
/*	TAKE CARE ABOUT REDIRECTION!!!							*/
/* -------------------------------------------------------- */
int	env(char **par)
{
	t_shell	*shell;
	t_env	*bak;
	char 	*param;

	param = par[1];
	if (param != NULL)
	{
		printf("env : option invalid '%s'\n", param);
		return (125);
	}
	shell = struct_passing(1, 0);
	bak = shell->env;
	while (shell->env != NULL && bak->env_var[0])
	{
		write (1, bak->env_var[0], ft_strlen(bak->env_var[0]));
		write (1, "=", 1);
		if (bak->env_var[1] != NULL)
			write (1, bak->env_var[1], ft_strlen(bak->env_var[1]));
		write (1, "\n", 1);
		if (bak->next_env != NULL)
			bak = bak->next_env;
		else
			break ;
	}
	return (0);
}
