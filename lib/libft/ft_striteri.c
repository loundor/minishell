/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:42:16 by stissera          #+#    #+#             */
/*   Updated: 2022/02/26 01:38:54 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	nbr;

	nbr = 0;
	if (s && f)
	{
		while (s[nbr])
		{
			(*f)(nbr, &(s[nbr]));
			nbr++;
		}
	}
}
