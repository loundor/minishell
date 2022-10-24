/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remaff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:50:15 by alfux             #+#    #+#             */
/*   Updated: 2022/10/04 02:46:16 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_affvar(char **av, char **ev, char ***var)
{
	int	ret;
	int	i;

	if (ft_root_parse(av, ev, *var))
		return (1);
	ret = ft_setvar(av, ev, var);
	i = 0;
	while (*(av + i))
	{
		(void)ft_free(*(av + i));
		*(av + i) = (char *)0;
		i++;
	}
	return (ret);
}

int	ft_remaff(char **av, char **ev, char ***var)
{
	int	check;
	int	i;

	if (!*av)
		return (0);
	check = ft_isntvar(av);
	if (!check)
		return (ft_affvar(av, ev, var));
	else if (check == 1)
		return (0);
	i = 0;
	while (i < check - 1)
		(void)ft_free(*(av + i++));
	i = 0;
	while (*(av + check - 1 + i))
	{
		*(av + i) = *(av + check - 1 + i);
		i++;
	}
	while (*(av + i))
		*(av + i++) = (char *)0;
	return (0);
}
