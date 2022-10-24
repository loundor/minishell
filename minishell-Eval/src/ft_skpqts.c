/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skpqts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:12:29 by alfux             #+#    #+#             */
/*   Updated: 2022/09/22 16:31:18 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	ft_skpqts(char *str, size_t start)
{
	char	c;

	if (!str || start < 0 || start > ft_strlen(str)
		|| (*(str + start) != 34 && *(str + start) != 39)
		|| !*(str + start + 1))
		return (0 * ft_errno(EINVAL));
	c = *(str + start++);
	while (*(str + start++) != c)
		if (!*(str + start))
			return (0 * ft_errno(EINVAL));
	return (start);
}
