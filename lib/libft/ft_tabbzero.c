/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabbzero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:14:13 by stissera          #+#    #+#             */
/*   Updated: 2022/09/20 09:17:07 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char **ft_tabbzero(char **tab, size_t count)
{
	size_t	i;

	i = 0;
	while (tab[i] && i <= count)
		tab[i++] = NULL;
	return (tab);
}