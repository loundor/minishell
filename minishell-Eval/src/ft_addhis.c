/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addhis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:20:05 by alfux             #+#    #+#             */
/*   Updated: 2022/08/30 19:27:03 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_addhis(char *pmt, char ***his)
{
	char	*new_his[2];
	char	**buf;

	if (!his || !pmt || !*his)
		return (ft_errno(EINVAL));
	new_his[0] = ft_strdup(pmt);
	if (!new_his[0])
		return (errno);
	new_his[1] = (char *)0;
	buf = ft_strtcat(*his, new_his);
	ft_free(*his);
	*his = buf;
	add_history(pmt);
	return (0);
}
