/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:04:04 by alfux             #+#    #+#             */
/*   Updated: 2022/09/11 10:51:15 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_shwarg(char **av, char opt)
{
	int	i;

	i = opt;
	while (*(av + i))
	{
		printf("%s", *(av + i++));
		if (*(av + i) && **(av + i - 1))
			printf(" ");
		else if (!*(av + i) && !opt)
			printf("\n");
	}
}

int	ft_echo(char **av)
{
	if (!av || !*av)
		return (ft_errmsg(EINVAL));
	if (!*(av + 1))
		return (0 * printf("\n"));
	av++;
	if (!ft_strncmp(*av, "-n", 3))
		ft_shwarg(av, 1);
	else
		ft_shwarg(av, 0);
	return (0);
}