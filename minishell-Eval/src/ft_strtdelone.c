/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:00:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/26 10:34:38 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strtdelone(char **addr, char ***tab)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (*(*tab + i))
		i++;
	new = ft_calloc(i, sizeof (char *));
	if (!new)
		return (1);
	i = 0;
	j = 0;
	while (*(*tab + i))
	{
		if (addr == *tab + i)
			ft_free(*addr + j++);
		else
			*(new + i - j) = *(*tab + i);
		i++;
	}
	ft_free(*tab);
	*tab = new;
	return (0);
}
