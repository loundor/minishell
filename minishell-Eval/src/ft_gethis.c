/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:28:46 by alfux             #+#    #+#             */
/*   Updated: 2022/09/25 23:50:11 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_remove_line_feed(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	if (*(str + size - 1) == '\n')
		*(str + size - 1) = '\0';
}

static char	*ft_addpth(char *path, char *fname)
{
	size_t	fsize;
	size_t	psize;
	char	*new;

	if (!path)
		return ((char *)(size_t)(0 * ft_errno(EINVAL)));
	fsize = ft_strlen(fname);
	psize = ft_strlen(path);
	new = ft_calloc(psize + fsize + 2, sizeof (char));
	if (!new)
		return ((char *)0);
	ft_strlcpy(new, path, psize + fsize + 2);
	ft_strlcpy(new + psize, "/", fsize + 2);
	ft_strlcpy(new + psize + 1, fname, fsize + 1);
	return (new);
}

int	ft_gethis(char *path, char *fname)
{
	char	*line;
	int		fd;

	fname = ft_addpth(path, fname);
	if (!fname)
		return (errno);
	fd = open(fname, O_RDONLY | O_CREAT, 0000600);
	(void)ft_free(fname);
	if (fd == -1)
		return (errno);
	line = get_next_line(fd + ft_errno(0));
	if (!line && errno)
		return (errno + (0 * close(fd)));
	while (line)
	{
		ft_remove_line_feed(line);
		add_history(line);
		(void)ft_free(line);
		line = get_next_line(fd + ft_errno(0));
		if (!line && errno)
			return (errno + (0 * close(fd)));
	}
	ft_errno(0);
	return (close(fd) * (-1) * errno);
}
