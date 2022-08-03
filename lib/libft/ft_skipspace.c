/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:54:34 by stissera          #+#    #+#             */
/*   Updated: 2022/08/03 18:18:28 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_skipspace(char *str)
{
	char	*ret;

	if (!str || *str == '\0')
		return (0);
	ret = str;
	while (*ret && (*ret == '\t' || *ret == '\n' || *ret == '\v'
			|| *ret == '\f' || *ret == '\r' || *ret == ' '))
		ret++;
	if (*ret == '\0')
		return (0);
	return (ret);
}
