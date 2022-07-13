/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:49:03 by stissera          #+#    #+#             */
/*   Updated: 2022/02/25 13:18:56 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	if (dstsize == 0)
		return (ft_strlen(src));
	count = 0;
	while (count < (dstsize - 1) && src[count])
	{
		*dst = src[count];
		dst++;
		count++;
	}
	*dst = '\0';
	while (src[count])
		count++;
	return (count);
}
