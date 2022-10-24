/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isextern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 02:14:04 by alfux             #+#    #+#             */
/*   Updated: 2022/09/07 02:23:38 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_cat_path_and_exe(char *path, char *exe, size_t esize)
{
	size_t	psize;
	char	*buf;

	psize = ft_strlen(path);
	buf = ft_calloc(psize + esize + 2, sizeof (char));
	if (!buf)
		return ((char *)0);
	ft_strlcpy(buf, path, psize + esize + 2);
	ft_strlcpy(buf + psize, "/", esize + 2);
	ft_strlcpy(buf + psize + 1, exe, esize + 1);
	return (buf);
}

static pid_t	ft_pthfnd(char *exe, char **av, char **ev, pid_t (*ex)(char *,
		char **, char **))
{
	size_t	esize;
	char	**whr;
	char	*buf;
	int		i;

	whr = ft_isvarin("PATH", ev);
	if (!whr)
		return (-2 + (0 * ft_errno(-4)));
	whr = ft_split(*whr + 5, ':');
	if (!whr)
		return (-2);
	i = 0;
	esize = ft_strlen(exe);
	while (*(whr + i))
	{
		buf = ft_cat_path_and_exe(*(whr + i++), exe, esize);
		if (!buf)
			return (-2 + ft_sfree(whr));
		if (!access(buf, F_OK) || ft_free(buf))
		{
			*av = buf + ft_free(*av) + ft_sfree(whr);
			return ((*ex)(*av, av, ev));
		}
	}
	return (-2 + ft_sfree(whr));
}

pid_t	ft_isextern(char **av, char **ev, pid_t (*ex)(char *, char **, char **))
{
	if (ft_isalnum(**av))
		return (ft_pthfnd(*av, av, ev, ex));
	else
		return ((*ex)(*av, av, ev));
}
