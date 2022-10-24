/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 03:55:37 by alfux             #+#    #+#             */
/*   Updated: 2022/09/25 23:49:33 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_addusr(char **ev, char *dir, int size)
{
	char	*usr;
	size_t	usize;
	int		i;

	i = 0;
	while (*(ev + i))
	{
		if (!ft_strncmp(*(ev + i), "USER=", 5))
		{
			usize = ft_strlen(*(ev + i) + 5);
			usr = ft_calloc(usize + size + 24, sizeof (char));
			if (!usr)
				return ((char *)(size_t)(ft_free(dir) * ft_errmsg(errno)));
			ft_strlcat(usr, "\001\033[32m\002", usize + size + 24);
			ft_strlcat(usr, *(ev + i) + 5, usize + size + 24);
			ft_strlcat(usr, "@minishell \001\033[0m\002", usize + size + 24);
			ft_strlcat(usr, dir, usize + size + 24);
			return (usr + ft_free(dir));
		}
		i++;
	}
	return (dir + (0 * ft_errmsg(-3)));
}

static char	*ft_ishome(char *path, char **ev)
{
	size_t	psize;
	char	**home;

	psize = ft_strlen(path);
	home = ft_isvarin("HOME", ev);
	if (!home)
		return (path);
	if (!ft_strncmp(path, *home + 5, psize + 1))
		return (ft_strdup("~") + ft_free(path));
	return (path);
}

static char	*ft_color_prompt(char **ev)
{
	char	*path;
	char	*dir;
	int		i;
	int		j;

	path = ft_newpwd();
	if (!path)
		return ((void *)0);
	path = ft_ishome(path, ev);
	if (!path)
		return ((void *)0);
	i = 0;
	j = 0;
	while (*(path + i))
		if (*(path + i++) == '/')
			j = i;
	dir = ft_calloc(i - j + 18, sizeof (char));
	if (!dir)
		return ((char *)(size_t)(ft_errmsg(errno) * ft_free(path)));
	ft_strlcat(dir, "\001\033[33m\002", i - j + 18);
	ft_strlcat(dir, path + j, i - j + 18);
	(void)ft_free(path);
	ft_strlcat(dir, " -> ", i - j + 18);
	ft_strlcat(dir, "\001\033[0m\002", i - j + 18);
	return (ft_addusr(ev, dir, i - j + 18));
}

char	*ft_prompt(char **ev, char ***his)
{
	char	*pmt;
	char	*ret;

	pmt = ft_color_prompt(ev);
	if (!pmt)
		return ((char *)(size_t)(0 * ft_errmsg(errno)));
	ft_sighdl(HDL_PROMPT_SIGINT);
	ret = readline(pmt);
	ft_sighdl(HDL_IGNORE_SIGINT);
	(void)ft_free(pmt);
	if ((ret && *ret && !ft_addhis(ret, his)) || (ret && !*ret))
		return (ret);
	else if (ret)
		return (ret + (0 * ft_errmsg(-6)));
	return ((char *)0);
}
