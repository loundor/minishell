/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:00:26 by stissera          #+#    #+#             */
/*   Updated: 2022/07/19 11:46:50 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	err_type(int msg, void *data)
{
	if (msg == 1)
		free((t_env *)data);
	if (msg == 2)
	{
		err_type(1, (t_shell *)data);
		free ((t_builtins *)((t_shell *)data)->builtin);
	}
}

int	ft_exit(int type, int to_free, void *data)
{
	if (type == 1)
		printf("Can't create environement structure!");
	else if (type == 2)
		printf("Malloc error!");
	else if (type == 3)
		printf("Welcome error!");
	else if (type == 4)
		printf("No environement variable!");
	else if (type == 5)
		printf("Signal modification not autorized");
	else if (type == 6)
		printf("Can't create builtins!");
	if (to_free)
		err_type(to_free, data);
	exit (type);
}
