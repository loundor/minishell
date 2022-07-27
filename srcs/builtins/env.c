/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:18:27 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 12:25:55 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ----------------| WRITE THE ENV VAR |------------------- */
/*	Just take the struct env and print all line separed by =*/
/*	index 0 = VAR NAME						index 1 = VALUE	*/
/*	TAKE CARE ABOUT REDIRECTION!!!							*/
/* -------------------------------------------------------- */
int	env(t_shell *shell)
{
	t_env	*bak;

	bak = shell->env;
	while (bak->env_var[0])
	{
		write (1, bak->env_var[0], ft_strlen(bak->env_var[0]));
		write (1, "=", 1);
		write (1, bak->env_var[1], ft_strlen(bak->env_var[1]));	// fd a modifier.. ATTENTION A LA LONGUEUR DE CETTE LIGNE!!!!
		write (1, "\n", 1);
		if (bak->next_env != NULL)
			bak = bak->next_env;
		else
			break ;
	}
	return (0);
}
