/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:54:34 by stissera          #+#    #+#             */
/*   Updated: 2022/07/20 10:42:48 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_skipspace(char *str)
{
	char	*ret;
	size_t	i;

	if (!str)
		return (0);
	ret = str;
	i = 0;
	while (ret[i] && (ret[i] != '\t' || ret[i] != '\n' || ret[i] != '\v'
			|| ret[i] != '\f' || ret[i] != 'r' || ret[i] != ' '))
		i++;
	if (ret[i] == '\0')
		return (0);
	return (ret);
}
