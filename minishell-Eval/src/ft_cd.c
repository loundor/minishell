/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 17:14:43 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_replace(char **pwd, char **old)
{
	size_t	size;
	char	*new;
	char	*buf;

	buf = ft_newpwd();
	if (!buf)
		return (1);
	size = ft_strlen(*pwd);
	new = ft_calloc(size + 4, sizeof (char));
	if (!new)
		return (1 + ft_free(buf));
	ft_free(*old);
	ft_strlcpy(new, "OLD", size + 4);
	ft_strlcpy(new + 3, *pwd, size + 1);
	*old = new;
	size = ft_strlen(buf);
	new = ft_calloc(size + 5, sizeof (char));
	if (!new)
		return (1 + ft_free(buf));
	ft_free(*pwd);
	*pwd = new;
	ft_strlcpy(*pwd, "PWD=", size + 5);
	ft_strlcpy(*pwd + 4, buf, size + 1);
	return (ft_free(buf));
}

static char	**ft_add_oldpwd(char **ev, char **new_ev)
{
	size_t	size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(ev + i))
	{
		if (!ft_strncmp(*(ev + i), "PWD=", 4))
		{
			*(new_ev + i + j) = *(ev + i);
			size = ft_strlen(*ev + i);
			*(new_ev + i + ++j) = ft_calloc(size + 4, sizeof (char));
			if (!*(new_ev + i + j))
				return ((char **)(size_t)ft_free(new_ev));
			ft_strlcpy(*(new_ev + i + j), "OLD", size + 4);
			ft_strlcpy(*(new_ev + i + j) + 3, *(ev + i), size + 1);
		}
		else
			*(new_ev + i + j) = *(ev + i);
		i++;
	}
	return (new_ev + ft_free(ev));
}

static char	**ft_find_oldpwd(char **ev)
{
	char	**new_ev;
	int		i;

	i = 0;
	while (*(ev + i))
		if (!ft_strncmp(*(ev + i++), "OLDPWD=", 7))
			return (ev);
	new_ev = ft_calloc(ft_strtlen(ev) + 2, sizeof (char *));
	if (!new_ev)
		return ((char **)0);
	return (ft_add_oldpwd(ev, new_ev));
}

static char	*ft_find_home(char **ev)
{
	int	i;

	i = 0;
	while (*(ev + i))
		if (!ft_strncmp(*(ev + i++), "HOME=", 5))
			return (*(ev + i - 1) + 5);
	return ((char *)0);
}

int	ft_cd(char **av, char ***ev, char **var)
{
	char	**new_ev;
	int		i;

	if (ft_strtlen(av) > 2)
		return (ft_errmsg(E2BIG));
	new_ev = ft_find_oldpwd(*ev);
	if (!new_ev)
		return (ft_errmsg(errno));
	*ev = new_ev;
	if (!*(av + 1))
	{
		if (chdir(ft_find_home(new_ev)))
			return (ft_errmsg(errno));
	}
	else if (chdir(*(av + 1)) && (ft_cdpath(*(av + 1), *ev, var) || ft_pwd(0)))
		return (ft_errmsg(errno));
	i = 0;
	while (*(new_ev + i))
	{
		if (!ft_strncmp(*(new_ev + i), "PWD=", 4))
			if (ft_replace(new_ev + i, new_ev + i + 1))
				return (ft_errmsg(errno));
		i++;
	}
	return (0);
}
