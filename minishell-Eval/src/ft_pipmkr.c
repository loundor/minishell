/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipmkr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:02:01 by alfux             #+#    #+#             */
/*   Updated: 2022/09/23 18:31:42 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_ispipe(char **av)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*(av + i))
	{
		if (!ft_strncmp(*(av + i), "(", 2))
			i = ft_skppar(av, i);
		else if (!ft_strncmp(*(av + i), "|", 2))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_to_next_pipe(char **av, int start)
{
	if (!ft_strncmp(*(av + start), "|", 2))
		start++;
	while (*(av + start) && ft_strncmp(*(av + start), "|", 2))
	{
		if (!ft_strncmp(*(av + start), "(", 2))
			start = ft_skppar(av, start);
		else
			start++;
	}
	return (start);
}

static char	**ft_sub_and_connect(char **av, int *fd, int *pfd, pid_t *pid)
{
	char	**cmd;

	*pid = 0;
	if (ft_sighdl(HDL_REINIT_SIGINT | HDL_REINIT_SIGQUIT) == -1)
		return ((char **)-1);
	if (*(fd + 1) && (dup2(*(fd + 1), 1) < 0 || close(*(fd + 1)) || close(*fd)))
		return ((char **)-1);
	if (*pfd && (dup2(*pfd, 0) < 0 || close(*pfd) || close(*(pfd + 1))))
		return ((char **)-1);
	cmd = ft_substrt(av, 0, ft_to_next_pipe(av, 0));
	if (!cmd)
		return ((char **)-1);
	return (cmd);
}

static char	**ft_fork_and_pipe(char **av, pid_t *pid, int count)
{
	int		fd[2];
	int		pfd[2];
	int		i;

	ft_bzero(pfd, sizeof (int) * 2);
	i = 0;
	while (i < count)
	{
		ft_bzero(fd, sizeof (int) * 2);
		if (i < count - 1)
			if (pipe(fd))
				return ((char **)-1 + (0 * close(pfd[0]) * close(pfd[1])));
		*(pid + i) = fork();
		if (!*(pid + i++))
			return (ft_sub_and_connect(av, fd, pfd, pid));
		if (pfd[0] && pfd[1])
			if (close(pfd[0]) || close(pfd[1]))
				return ((char **)-1);
		pfd[0] = fd[0];
		pfd[1] = fd[1];
		av += ft_to_next_pipe(av, 0);
		if (*av)
			av++;
	}
	return ((char **)0);
}

char	**ft_pipmkr(char **av, pid_t **pid)
{
	char	**cmd;
	int		count;

	count = ft_ispipe(av);
	if (!count)
		return (av);
	*pid = ft_calloc(count + 2, sizeof (pid_t));
	if (!*pid)
		return ((char **)-1);
	**pid = -1;
	cmd = ft_fork_and_pipe(av, *pid, count + 1);
	return (cmd);
}
