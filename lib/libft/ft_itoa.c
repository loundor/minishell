/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:18:11 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 23:44:42 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	*ft_itoawrite(long n, int neg, int size)
{
	char	*ret;

	ret = (char *) malloc(sizeof(char) * size + neg + 1);
	if (!ret)
		return (0);
	ret[size + neg] = '\0';
	if (neg == 1)
		ret[0] = '-';
	while (size > 0)
	{
		ret[size + neg - 1] = (n % 10) + 48;
		n /= 10;
		size--;
	}
	return (ret);
}

static char	*ft_itoazero(void)
{
	char	*ret;

	ret = (char *) malloc(sizeof(char) * 2);
	ret[0] = (char) 48;
	ret[1] = 0;
	return (ret);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		size;
	long	ssize;
	long	len;

	if (!n || n == 0)
		return (ft_itoazero());
	ssize = n;
	neg = 0;
	size = 0;
	if (ssize < 0)
	{
		neg = 1;
		ssize *= -1;
	}
	len = ssize;
	while (len > 0)
	{
		size++;
		len /= 10;
	}
	return (ft_itoawrite(ssize, neg, size));
}
