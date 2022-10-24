/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isntvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/10/07 16:41:40 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isntvar(char **cmd)
{
	size_t	j;
	int		i;

	if (!cmd)
		return (1);
	i = 0;
	while (*(cmd + i))
	{
		j = 0;
		while (*(*(cmd + i) + j))
		{
			if ((j == 0 && ft_isdigit(*(*(cmd + i + j))))
				|| (!ft_isalnum(*(*(cmd + i) + j))
					&& *(*(cmd + i) + j) != '_') || !*(*(cmd + i) + j + 1))
			{
				if (j > 0 && *(*(cmd + i) + j) == '=')
					break ;
				return (i + 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
