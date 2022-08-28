/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:56:26 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 12:58:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ------------| NEED EXIT??! PREVENT LEAKS! |------------- */
/*	The function tale a type of "error" and put a message	*/
/*	in a screen. If there are something to free (level)		*/
/*	We call the err_type with the code/level to free and	*/
/*	exit the program without leaks.							*/
/*	TO_FREE= 0-Nothing; 1-SHELL; 2-ENV; 3-CMD; 4-BUILTINS	*/
/* -------------------------------------------------------- */

static void	err_type(int to_free, void *data)
{
	if (to_free == 1)
		free_shell((t_shell *)data);
	if (to_free == 2)
		free_env((t_env *)data);
	if (to_free == 3)
		free_cmd((t_cmd *)data);
	if (to_free == 4)
		free_builtins((t_builtins *)data);
}

int	ft_exit(int type, int to_free)
{
	if (to_free)
		err_type(to_free, struct_passing(to_free, 0));
	return (ft_errmsg(type));
}