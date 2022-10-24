/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:57 by alfux             #+#    #+#             */
/*   Updated: 2022/09/16 17:51:11 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

pid_t	ft_waitall(pid_t *pid, int *last_status, int opt)
{
	pid_t	ret;
	int		first_status;
	int		i;

	ret = 0;
	if (!pid)
		ret = waitpid(0, last_status, opt);
	first_status = (*last_status) * (!pid);
	i = 0;
	while (pid && *(pid + i))
	{
		if (i == 0)
			ret = waitpid(*(pid + i), &first_status, opt);
		else if (!*(pid + i + 1))
			ret = waitpid(*(pid + i), last_status, opt);
		else
			ret = waitpid(*(pid + i), (int *)0, opt);
		i++;
	}
	ft_sigmsg(first_status, *last_status);
	return (ret);
}
