/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:26:31 by alfux             #+#    #+#             */
/*   Updated: 2022/08/25 17:52:19 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_strtdup(char **tab)
{
	char	**new_tab;
	int		i;

	new_tab = ft_calloc(ft_strtlen(tab) + 1, sizeof (char *));
	if (!new_tab)
		return ((char **)0);
	i = 0;
	while (*(tab + i))
	{
		*(new_tab + i) = ft_strdup(*(tab + i));
		if (!*(new_tab + i))
			return ((char **)(size_t)ft_sfree(new_tab));
		i++;
	}
	return (new_tab);
}
