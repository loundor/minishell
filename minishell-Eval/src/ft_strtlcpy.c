/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtlcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:21:35 by alfux             #+#    #+#             */
/*   Updated: 2022/09/05 20:27:13 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strtlcpy(char **dst, char **src, int dstsize)
{
	int	i;

	i = 0;
	while (*(src + i) && i < dstsize - 1)
	{
		*(dst + i) = ft_strdup(*(src + i));
		if (!*(dst + i))
			return (ft_sfree(dst));
		i++;
	}
	if (dstsize)
		*(dst + i) = (char *)0;
	while (*(src + i))
		i++;
	return (i);
}
