/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:02:04 by alfux             #+#    #+#             */
/*   Updated: 2022/09/05 20:31:02 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_substrt(char **strt, int start, int len)
{
	char	**sub;
	int		size;

	if (!strt)
		return ((char **)0);
	size = ft_strtlen(strt);
	if (start > size)
		return ((char **)0);
	if (size - start < len)
		len = size - start;
	sub = ft_calloc(len + 1, sizeof (char *));
	if (sub)
		ft_strtlcpy(sub, strt + start, len + 1);
	return (sub);
}
