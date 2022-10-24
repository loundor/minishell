/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skppar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:34:09 by alfux             #+#    #+#             */
/*   Updated: 2022/09/22 19:57:14 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_skppar(char **strt, int start)
{
	size_t	par;

	if (!strt || start < 0 || ft_strtlen(strt) <= (size_t)start)
		return (0 * ft_errno(EINVAL));
	if (ft_strncmp(*(strt + start), "(", 2))
		return (0);
	par = 1;
	while (*(strt + ++start) && par)
	{
		if (!ft_strncmp(*(strt + start), "(", 2))
			par++;
		else if (!ft_strncmp(*(strt + start), ")", 2))
			par--;
	}
	if (par)
		return (0 * ft_errno(EINVAL));
	return (start);
}
