/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:04:04 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 08:46:50 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_shwarg(char **av, char opt)
{
	int	i;

	i = 0;
	while (*(av + i))
	{
		ft_printf("%s", *(av + i++));
		if (*(av + i) && **(av + i - 1))
			ft_printf(" ");
		else if (!*(av + i) && !opt)
			ft_printf("\n");
	}
}

int	ft_echo(char **av)
{
	if (!av || !*av)
		return (ft_errmsg(EINVAL));
	if (!*(av + 1))
		return (0 * ft_printf("\n"));
	av++;
	if (!ft_strncmp(*av, "-n", 3))
	{
		av++;
		while (*av && !ft_strncmp(*av, "-n", 3))
			av++;
		ft_shwarg(av, 1);
	}
	else
		ft_shwarg(av, 0);
	return (0);
}
