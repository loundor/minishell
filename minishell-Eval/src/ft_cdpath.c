/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:13:52 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 16:49:20 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_chdir(char *path, char *cdpath)
{
	char	**split;
	char	*join;
	int		i;

	split = ft_split(cdpath, ':');
	if (!split)
		return (1);
	i = 0;
	while (*(split + i))
	{
		join = ft_strjoin(*(split + i), path);
		if (!join)
			break ;
		if (!chdir(join))
			return (ft_sfree(split) + ft_free(join));
		(void)ft_free(join);
		i++;
	}
	(void)ft_sfree(split);
	return (1);
}

int	ft_cdpath(char *path, char **ev, char **var)
{
	char	**cdpath;
	int		ret;

	if (*path == '/')
		return (1);
	cdpath = ft_isvarin("CDPATH", ev);
	if (!cdpath)
		cdpath = ft_isvarin("CDPATH", var);
	if (!cdpath)
		return (1);
	path = ft_strjoin("/", path);
	if (!path)
		return (1);
	ret = ft_chdir(path, *cdpath + 7);
	(void)ft_free(path);
	return (ret);
}
