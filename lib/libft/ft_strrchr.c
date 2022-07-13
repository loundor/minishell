/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 01:08:36 by stissera          #+#    #+#             */
/*   Updated: 2022/02/26 01:48:30 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*ret;

	str = (char *)s;
	ret = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			ret = str;
		str++;
	}
	if (c == '\0')
		return (str);
	return (ret);
}
