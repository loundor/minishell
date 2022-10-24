/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 04:59:20 by alfux             #+#    #+#             */
/*   Updated: 2022/09/24 01:02:33 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_stdio(int flag)
{
	static int	fd_stdout;
	static int	fd_stdin;

	if (flag == SAVE_IO)
	{
		fd_stdout = dup(1);
		fd_stdin = dup(0);
		if (fd_stdout == -1 || fd_stdin == -1)
			return (-1);
	}
	else if (flag == CLOSE_IO)
	{
		if (fd_stdin && fd_stdout && (close(fd_stdout) || close(fd_stdin)))
			return (-1);
		fd_stdout = 0;
		fd_stdin = 0;
	}
	else if (flag == RESET_OUT)
		return (dup2(fd_stdout, 1));
	else if (flag == RESET_IN)
		return (dup2(fd_stdin, 0));
	else if (flag == RESET_IO)
		if (dup2(fd_stdout, 1) == -1 || dup2(fd_stdin, 0) == -1)
			return (-1);
	return (0);
}
