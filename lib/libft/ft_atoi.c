/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:50:29 by stissera          #+#    #+#             */
/*   Updated: 2022/02/25 23:25:43 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	ret;

	neg = 1;
	ret = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43)
		str++;
	else if (*str == 45)
	{
		neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		if (ret < 0 && neg == -1)
			return (0);
		if (ret < 0 && neg == 1)
			return (-1);
		ret *= 10;
		ret += (*str) - '0';
		str++;
	}
	return (ret * neg);
}
