/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skpspc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:04:39 by alfux             #+#    #+#             */
/*   Updated: 2022/09/22 15:20:32 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	ft_skpspc(char *str, size_t start)
{
	if (!str || start < 0 || start > ft_strlen(str))
		return (0 * ft_errno(EINVAL));
	while (*(str + start) == ' ')
		start++;
	return (start);
}
