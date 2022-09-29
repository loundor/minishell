/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:26:15 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 15:32:44 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -------------| ENVIRONNEMENT VARIABLES  |--------------- */
/*	Parse all env in a struct t_env							*/
/*	Struct : env_var	[0] NAME OF VARIALBLE				*/
/*						[1] VARIABLES						*/
/*	Can add variable with export very easy					*/
/*	Need to put all variable in a **char the execve			*/
/* -------------------------------------------------------- */

void	do_env(char **env)
{
	while (*env != 0)
	{
		add_env_line(*env);
		env++;
	}
	return ;
}
