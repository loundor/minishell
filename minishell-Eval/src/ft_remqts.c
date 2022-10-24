/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remqts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:30:16 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 05:38:46 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_cut_and_link(char **str, size_t *i)
{
	char	*begin;
	char	*end;
	char	*new;

	begin = ft_substr(*str, 0, *i);
	end = ft_substr(*str, *i + 1, ft_skpqts(*str, *i) - *i - 2);
	if (!begin || !end)
		return (-1 + ft_free(begin) + ft_free(end));
	new = ft_strjoin(begin, end);
	(void)ft_free(begin);
	begin = new;
	(void)ft_free(end);
	end = ft_strdup(*str + ft_skpqts(*str, *i));
	if (!begin || !end)
		return (-1 + ft_free(begin) + ft_free(end));
	new = ft_strjoin(begin, end);
	(void)ft_free(begin);
	(void)ft_free(end);
	if (!new)
		return (-1);
	*i = ft_skpqts(*str, *i) - 2;
	(void)ft_free(*str);
	*str = new;
	return (0);
}

int	ft_remqts(char **str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return (-1 + (0 * ft_errno(EINVAL)));
	while (*(*str + i))
	{
		if (*(*str + i) == '\'' || *(*str + i) == '\"')
		{
			if (ft_cut_and_link(str, &i))
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
