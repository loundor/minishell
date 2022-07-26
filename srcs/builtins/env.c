/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:18:27 by stissera          #+#    #+#             */
/*   Updated: 2022/07/26 22:42:09 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* ---------------|					 |------------------- */
/*															*/
/* -------------------------------------------------------- */
int	env(t_shell *shell)
{
	t_env	*bak;
	size_t	roll[2];

	bak = shell->env;
	roll[0] = 0;
	roll[1] = -1;
	while (ft_strncmp(bak->env_var[0], shell->env->env_var[0],
			ft_strlen(shell->env->env_var[0]))
		|| (!ft_strncmp(bak->env_var[0], shell->env->env_var[0],
				ft_strlen(shell->env->env_var[0])) && roll[0] != 1))
	{
		write (1, bak->env_var[0], ft_strlen(bak->env_var[0]));
		write (1, "=", 1);
		while (bak->env_var[++roll[1]])
		{	
			if (roll[1] > 0)
				write(1, ":", 1);
			write (1, bak->env_var[roll[1]], ft_strlen(bak->env_var[roll[1]]));	// fd a modifier.. ATTENTION A LA LONGUEUR DE CETTE LIGNE!!!!
		}
		roll[1] = -1;
		write (1, "\n", 1);
		bak = bak->next_env;
		roll[0] = 1;
	}
	return (0);
}
