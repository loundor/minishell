/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:17:43 by alfux             #+#    #+#             */
/*   Updated: 2022/08/25 17:50:52 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_strtcat(char **t1, char **t2)
{
	size_t	i;
	char	**new;

	if (!t1 || !t2)
	{
		errno = EINVAL;
		return ((char **)0);
	}
	new = ft_calloc(ft_strtlen(t1) + ft_strtlen(t2) + 1, sizeof (char *));
	if (!new)
		return ((char **)0);
	i = 0;
	while (*(t1 + i))
	{
		*(new + i) = *(t1 + i);
		i++;
	}
	t1 = new + i;
	i = 0;
	while (*(t2 + i))
	{
		*(t1 + i) = *(t2 + i);
		i++;
	}
	return (new);
}
