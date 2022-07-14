/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:00:26 by stissera          #+#    #+#             */
/*   Updated: 2022/07/14 13:24:29 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	err_type(int msg, void *data)
{
	t_shell	*shell;
	t_env	*env;

	if (msg == 1)
	{
		env = data;
		free(env);
	}
	return (0);
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
		printf("...!");
	else if (type == 6)
		printf("...!");
	if (to_free)
		err_type(to_free, data);
	exit (type);
}
