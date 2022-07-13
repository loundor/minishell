/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:40:26 by stissera          #+#    #+#             */
/*   Updated: 2022/02/25 14:51:20 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if (len == 0 || !s || (ft_strlen(s) < start))
	{
		ret = (char *) malloc(sizeof(char) * 1);
		*ret = '\0';
		return (ret);
	}
	ret = (char *) malloc(sizeof(char) * (len) +1);
	if (!ret)
		return (NULL);
	while (i < len && *s)
	{
		ret[i] = s[i + start];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
