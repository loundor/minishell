/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:29:03 by stissera          #+#    #+#             */
/*   Updated: 2022/02/25 11:57:39 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long int	count;
	unsigned char		*dest_cast;

	if (dest == NULL && src == NULL)
		return (NULL);
	count = 0;
	dest_cast = (unsigned char *) dest;
	while (count < n)
	{
		dest_cast[count] = *(unsigned char *)src;
		src++;
		count++;
	}
	return (dest);
}
