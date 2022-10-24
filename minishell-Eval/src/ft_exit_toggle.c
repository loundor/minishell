/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_toggle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:42:55 by alfux             #+#    #+#             */
/*   Updated: 2022/10/07 16:29:01 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

static int	ft_check_int(char *num)
{
	size_t	i;

	if (!num || !*num)
		return (0);
	i = 0;
	while (ft_isspace(*(num + i)))
		i++;
	if (*(num + i) == '-' || *(num + i) == '+')
		i++;
	while (ft_isdigit(*(num + i)))
		i++;
	while (ft_isspace(*(num + i)))
		i++;
	if (*(num + i))
		return (0);
	return (1);
}

int	ft_exit_toggle(int toggle, char *ex_sav, int *ex_get)
{
	static int	status;
	static int	exit_status;
	static int	isset;

	if (ex_sav && !isset)
	{
		if (ft_check_int(ex_sav))
			exit_status = ft_atoi(ex_sav);
		else
		{
			exit_status = 255;
			ft_putstr_fd("Error: exit: numeric argument required\n", 2);
		}
		isset = 1;
	}
	if (ex_get)
		*ex_get = exit_status;
	if (toggle)
		status = toggle;
	return (status);
}
