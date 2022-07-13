/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:39:56 by stissera          #+#    #+#             */
/*   Updated: 2022/02/26 12:10:28 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	count;
	char	*ret;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	count = 0;
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	while (count < len)
	{
		ret[count] = (*f)(count, s[count]);
		count++;
	}
	ret[count] = '\0';
	return (ret);
}
