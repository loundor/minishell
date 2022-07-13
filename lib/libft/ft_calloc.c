/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:12:59 by stissera          #+#    #+#             */
/*   Updated: 2022/02/24 20:34:12 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	ccount;
	char	*ret;

	ret = NULL;
	ret = (char *)malloc(size * count);
	if (!ret)
		return (NULL);
	ccount = 0;
	while (ccount < (size * count))
	{
		ret[ccount] = 0;
		ccount++;
	}
	return ((void *)ret);
}
