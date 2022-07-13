/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:09:16 by stissera          #+#    #+#             */
/*   Updated: 2022/02/26 12:09:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_start(const char *s1, const char *set)
{
	size_t	len;
	size_t	count;

	len = ft_strlen(s1);
	count = 0;
	while (len > count)
	{
		if (ft_strchr(set, s1[count]) == 0)
			break ;
		count++;
	}
	return (count);
}

static int	ft_end(const char *s1, const char *set)
{
	size_t	len;
	size_t	count;

	len = ft_strlen(s1);
	count = 0;
	while (len > count)
	{
		if (ft_strchr(set, s1[len - count - 1]) == 0)
			return (len - count);
		count++;
	}
	return (len - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (set == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
