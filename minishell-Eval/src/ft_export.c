/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:56:46 by alfux             #+#    #+#             */
/*   Updated: 2022/10/07 17:37:08 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_alphaprint(char **ev, char const *prv)
{
	char	*print;
	int		i;

	i = 0;
	print = (char *)0;
	while (*(ev + i))
	{
		if ((!*prv || ft_strncmp(*(ev + i), prv, ft_maxof(ft_strlen(*(ev + i)),
						ft_strlen(prv))) < 0) && (!print || ft_strncmp(*(ev + i)
					, print, ft_maxof(ft_strlen(print),
						ft_strlen(*(ev + i)))) > 0))
			print = *(ev + i);
		i++;
	}
	if (!print)
		return (0);
	(void)ft_alphaprint(ev, print);
	ft_printf("declare -x %c", *print);
	while (*(++print) && *(print - 1) != '=')
		ft_putchar_fd(*print, 1);
	ft_putchar_fd('\"', 1);
	ft_printf("%s\"\n", print);
	return (0);
}

static int	ft_iseq(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0 * ft_errmsg(EINVAL));
	str++;
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (*str == '=')
		return (1);
	if (*str)
		ft_errmsg(EINVAL);
	return (0);
}

static char	**ft_equalities(char **av)
{
	char	**cpy;
	int		size;
	int		i;
	int		j;

	size = ft_strtlen(av);
	cpy = ft_calloc(size + 1, sizeof (char *));
	if (!cpy)
		return ((char **)0);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (ft_iseq(*(av + i)))
			*(cpy + j++) = *(av + i);
		i++;
	}
	return (cpy);
}

static char	**ft_toadd(char **av, char **ev, char ***var)
{
	char	**add;
	char	**buf;
	int		i;
	int		j;

	add = ft_calloc(ft_strtlen(av) + 1, sizeof (char *));
	if (!add)
		return ((char **)0);
	i = -1;
	j = 0;
	while (*(av + ++i))
	{
		buf = ft_isvarin(*(av + i), ev);
		if (!buf)
		{
			buf = ft_isvarin(*(av + i), *var);
			if (buf)
			{
				*(add + j) = ft_strdup(*buf);
				if (!*(add + j++) || ft_strtdelone(buf, var))
					return ((char **)(size_t)ft_sfree(add));
			}
		}
	}
	return (add);
}

int	ft_export(char **av, char ***ev, char ***var)
{
	char	**buf;
	char	**add;

	(void)ft_errno(0);
	if (!*(av + 1))
		return (ft_alphaprint(*ev, "\0"));
	buf = ft_equalities(av);
	if (!buf)
		return (ft_errmsg(errno));
	if (*buf)
		(void)ft_setvar(buf, *ev, var);
	(void)ft_free(buf);
	add = ft_toadd(av, *ev, var);
	if (!add)
		return ((-1) * ft_errmsg(-5 + (0 * ft_errmsg(errno))));
	buf = ft_strtcat(*ev, add);
	if (!buf)
		return ((-1) * ft_errmsg(-5 + (0 * ft_errmsg(errno))) + ft_sfree(add));
	ft_free(*ev);
	ft_free(add);
	*ev = buf;
	return (!!errno << 8);
}
