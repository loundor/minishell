/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:27:44 by stissera          #+#    #+#             */
/*   Updated: 2022/02/24 23:28:04 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast;

	cast = (unsigned char *)s;
	while (n)
	{
		if (*cast == (unsigned char)c)
			return ((void *)cast);
		cast++;
		n--;
	}
	return (NULL);
}
