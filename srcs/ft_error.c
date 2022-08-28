/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:00:26 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 12:56:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	tab_err(int type)
{
	static char	*msg_err[8];

	if (!msg_err[0])
	{
		msg_err[0] = "Can't create environement structure!";
		msg_err[1] = "Malloc error!";
		msg_err[2] = "Welcome error!";
		msg_err[3] = "No environement variable!";
		msg_err[4] = "Signal modification not autorized";
		msg_err[5] = "Can't create builtins!";
		msg_err[6] = "Error command not found!\n";
	}
	if (type != 0)
		printf("%s", msg_err[type + 1]);
}

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

