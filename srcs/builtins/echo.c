/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:04:04 by alfux             #+#    #+#             */
/*   Updated: 2022/09/15 14:39:08 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_shwarg(char **av, char opt)
{
	int	i;

	i = opt;
	while (*(av + i))
	{
		ft_putstr_fd(*(av + i++), 1);
		if (*(av + i) && **(av + i - 1))
			ft_putchar_fd(' ', 1);
		else if (!*(av + i) && !opt)
			ft_putchar_fd('\n', 1);
	}
}

int	ft_echo(char **av)
{
	if (!av || !*av)
		return (ft_errmsg(EINVAL));
	if (!*(av + 1))
		return (0 * printf("\n"));
	av++;
	if (!ft_strncmp(*av, "-n\0", 3))
		ft_shwarg(av, 1);
	else
		ft_shwarg(av, 0);
	return (0);
}
