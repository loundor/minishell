/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:20:04 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 22:10:03 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_check_param(char *av)
{
	while (*av)
	{
		if (!ft_isalnum(*av) && *av != '_')
			return (0);
		av++;
	}
	return (1);
}

int	ft_unset(char **av, char ***ev, char ***var)
{
	char	**buf;
	int		i;

	i = -1 + ft_errno(0);
	while (*(av + ++i))
	{
		if (ft_check_param(*(av + i)))
		{
			buf = ft_isvarin(*(av + i), *var);
			if (buf)
			{
				if (ft_strtdelone(buf, var))
					return (ft_errmsg(errno));
			}
			else
			{
				buf = ft_isvarin(*(av + i), *ev);
				if (buf && ft_strtdelone(buf, ev))
					return (ft_errmsg(errno));
			}
		}
		else
			ft_errmsg(EINVAL);
	}
	return (errno);
}
