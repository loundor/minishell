/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:26:30 by stissera          #+#    #+#             */
/*   Updated: 2022/09/16 23:27:57 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_cnttab(char **array)
{
	size_t i;

	if (!array)
		return (0);
	
	i = 0;
	while (array[i] && array[i] != NULL)
		i++;
	return (i);
}