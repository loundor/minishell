/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 04:59:20 by alfux             #+#    #+#             */
/*   Updated: 2022/09/24 01:02:41 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_setio(int flag)
{
	static int	fd_out;
	static int	fd_in;

	if (flag == SAVE_IO)
	{
		fd_out = dup(1);
		fd_in = dup(0);
		if (fd_out == -1 || fd_in == -1)
			return (-1);
	}
	else if (flag == CLOSE_IO)
	{
		if (fd_in && fd_out && (close(fd_out) || close(fd_in)))
			return (-1);
		fd_out = 0;
		fd_in = 0;
	}
	else if (flag == RESET_OUT)
		return (dup2(fd_out, 1));
	else if (flag == RESET_IN)
		return (dup2(fd_in, 0));
	else if (flag == RESET_IO)
		if (dup2(fd_out, 1) == -1 || dup2(fd_in, 0) == -1)
			return (-1);
	return (0);
}
