/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:30:42 by alfux             #+#    #+#             */
/*   Updated: 2022/08/23 12:33:02 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	ft_strtlen(char **tab)
{
	size_t	i;

	if (!tab)
		return (0 * ft_errmsg(EINVAL));
	i = 0;
	while (*(tab + i))
		i++;
	return (i);
}
