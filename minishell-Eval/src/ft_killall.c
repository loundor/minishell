/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_killchildren.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:47:26 by alfux             #+#    #+#             */
/*   Updated: 2022/09/10 13:56:12 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_killall(pid_t *pid, int sig)
{
	int	i;

	if (!pid)
		return (0);
	i = 0;
	while (*(pid + i))
		(void)kill(*(pid + i++), sig);
	return (0);
}
