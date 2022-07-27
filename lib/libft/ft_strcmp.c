/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:58:53 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 11:00:10 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	count;

	count = 0;
	if ((*s1 == '\0' && *s2 == '\0'))
		return (0);
	while (s1[count])
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	if (s2[count] == '\0')
		return (0);
	else
		return (-s2[count]);
}
