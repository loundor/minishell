/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:00:55 by stissera          #+#    #+#             */
/*   Updated: 2022/02/24 20:36:11 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len;
	size_t	count;

	len = ft_strlen(dest);
	if (n < (len + 1))
		return (n + ft_strlen(src));
	count = (n - len - 1);
	while (*src && count)
	{
		dest[len] = *src;
		len++;
		src++;
		count--;
	}
	dest[len] = '\0';
	return (len + ft_strlen(src));
}
