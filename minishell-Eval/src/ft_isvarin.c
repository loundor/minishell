/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvarin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:55 by alfux             #+#    #+#             */
/*   Updated: 2022/08/25 17:26:38 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_isvarin(char *str, char **tab)
{
	size_t	size;
	int		i;

	if (!tab || !*tab)
		return ((char **)0);
	size = 0;
	while (*(str + size) && *(str + size) != '=')
		size++;
	i = 0;
	while (*(tab + i))
	{
		if (!ft_strncmp(str, *(tab + i), size) && *(*(tab + i) + size) == '=')
			return (tab + i);
		i++;
	}
	return ((char **)0);
}
