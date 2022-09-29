/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:18:16 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 16:02:21 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	count;
	char	*str;

	str = NULL;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1)) + 1);
	if (!str || s1 == NULL)
		return (NULL);
	count = 0;
	while (*s1)
	{
		str[count] = *s1;
		s1++;
		count++;
	}
	str[count] = '\0';
	return (str);
}
