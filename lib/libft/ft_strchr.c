/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:31:46 by stissera          #+#    #+#             */
/*   Updated: 2022/09/27 08:39:01 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	if (!s || !c)
		return (NULL);
	ret = (char *)s;
	while (*ret != '\0')
	{
		if (*ret == c)
			return (ret);
		ret++;
	}
	if (c == '\0')
		return (NULL);
	return ((char *)ret);
}
