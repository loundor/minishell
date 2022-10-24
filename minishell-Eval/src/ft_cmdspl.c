/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdspl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:10:20 by alfux             #+#    #+#             */
/*   Updated: 2022/09/09 06:16:34 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
//Modify to isolate correctly | < > << >> || &&
static size_t	ft_arglen(char *arg)
{
	size_t	i;
	char	quote;
	char	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (*(arg + i) && !(*(arg + i) == ' ' && !quote && !dquote))
	{
		if (!quote && *(arg + i) == 34)
			dquote = (dquote + 1) % 2;
		else if (!dquote && *(arg + i) == 39)
			quote = (quote + 1) % 2;
		i++;
	}
	if (quote)
		return (-1);
	if (dquote)
		return (-2);
	return (i);
}

static int	ft_argcnt(char *pmt)
{
	int		argc;
	size_t	argl;
	size_t	i;

	i = 0;
	argc = 0;
	while (*(pmt + i))
	{
		while (*(pmt + i) == ' ')
			i++;
		if (*(pmt + i))
			argc++;
		argl = ft_arglen(pmt + i);
		if (argl == (size_t)(-1))
			return (-1);
		else if (argl == (size_t)(-2))
			return (-2);
		i += argl;
	}
	return (argc);
}

char	**ft_cmdspl(char *pmt)
{
	char	**cmd;
	int		argc;
	int		argl;
	int		i;
	size_t	j;

	argc = ft_argcnt(pmt);
	if (argc < 0)
		return ((char **)(0 * (size_t)ft_errmsg(argc)));
	cmd = ft_calloc(argc + 1, sizeof (char *));
	if (!cmd)
		return ((char **)(0 * (size_t)ft_errmsg(errno)));
	i = 0;
	j = 0;
	while (i < argc)
	{
		while (*(pmt + j) == ' ')
			j++;
		argl = ft_arglen(pmt + j);
		*(cmd + i) = ft_substr(pmt, j, argl);
		if (!*(cmd + i++))
			return ((char **)(size_t)(ft_sfree(cmd) * ft_errmsg(errno)));
		j += argl;
	}
	return (cmd);
}
