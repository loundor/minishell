/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_savhis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:20:17 by alfux             #+#    #+#             */
/*   Updated: 2022/09/01 03:54:19 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_savhis(char *path, char *fname, char **his)
{
	size_t	size;
	char	*hist;
	int		fd;

	if (!path)
		return (ft_errmsg(-7 + (0 * ft_errmsg(EINVAL))));
	size = ft_strlen(path) + ft_strlen(fname);
	hist = ft_calloc(size + 2, sizeof (char));
	if (!hist)
		return (ft_errmsg(-7 + (0 * ft_errmsg(errno))));
	ft_strlcpy(hist, path, size + 2);
	ft_strlcat(hist, "/", size + 2);
	ft_strlcat(hist, fname, size + 2);
	ft_printf("Saving history in %s\n", hist);
	fd = open(hist, O_WRONLY | O_CREAT | O_APPEND, 0000600);
	if (fd == -1)
		return (ft_errmsg(errno) + ft_free(hist));
	while (*his)
	{
		ft_putstr_fd(*(his++), fd);
		ft_putchar_fd('\n', fd);
	}
	if (close(fd) == -1)
		return (ft_errmsg(errno) + ft_free(hist));
	return (ft_free(hist));
}
