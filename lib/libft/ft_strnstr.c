/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:57:16 by stissera          #+#    #+#             */
/*   Updated: 2022/02/24 20:35:38 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ret;
	size_t	count;
	int		i;

	ret = (char *)haystack;
	if (!*needle)
		return (ret);
	i = 0;
	count = 0;
	while (*ret != '\0' && count < len)
	{
		while ((ret[i] == needle[i]) && (count + i < len))
		{
			if (needle[i + 1] == '\0')
				return (ret);
			i++;
		}
		i = 0;
		count++;
		ret++;
	}
	return (NULL);
}
