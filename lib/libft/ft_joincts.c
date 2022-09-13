/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joincts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:35:45 by stissera          #+#    #+#             */
/*   Updated: 2022/09/13 13:56:20 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_joincts(const char *s, const char c)
{
	char	*ret;
	size_t	count;
	size_t	i;
	size_t	plus;

	count = ft_strlen(s);
	plus = 2;
	if (!c)
		plus = 1;
	ret = (char *)malloc(sizeof(char) * (count + plus));
	i = -1;
	while (++i < count)
		ret[i] = s[i];
	if (c)
		ret[i++] = c;
	ret[i] = '\0';
	return (ret);
}
