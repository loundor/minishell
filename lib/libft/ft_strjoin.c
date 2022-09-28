/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:17:54 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 20:47:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len[2];
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	len[0] = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (len[0] + ft_strlen(s2) + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			ret[i] = s1[i];
	i = -1;
	if (s2)
	{
		while (s2[++i])
		{
			ret[len[0]] = s2[i];
			len[0]++;
		}
	}
	ret[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ret);
}
