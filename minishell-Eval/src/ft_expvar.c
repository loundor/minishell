/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:21:32 by alfux             #+#    #+#             */
/*   Updated: 2022/10/07 17:29:31 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_cut_link(char **str, char *begin, char **v, char *end)
{
	size_t	i;
	char	*new;
	char	*middle;

	if (!v)
		middle = ft_strdup("");
	else
		middle = ft_strdup(*v);
	if (!begin || !middle || !end)
		return (-1 + ft_free(begin) + ft_free(middle) + ft_free(end));
	i = 0;
	while (*(middle + i) && *(middle + i++) != '=')
		;
	new = ft_strjoin(begin, middle + i);
	(void)ft_free(middle + ft_free(begin));
	if (!new)
		return (-1 + ft_free(end));
	begin = new;
	new = ft_strjoin(begin, end);
	(void)ft_free(end + ft_free(begin));
	if (!new)
		return (-1);
	(void)ft_free(*str);
	*str = new;
	return (0);
}

static size_t	ft_varlen(char **v)
{
	size_t	i;

	if (!v)
		return (0);
	i = 0;
	while (*(*v + i))
		if (*(*v + i++) == '=')
			break ;
	return (ft_strlen(*v + i));
}

static size_t	ft_insert(char **str, size_t *i, char **ev, char **var)
{
	size_t	j;
	char	*sub;
	char	**v;

	j = 1;
	if (*(*str + *i + j) == '?')
		v = var + (0 * j++);
	else
	{
		while (*(*str + *i + j) && (j != 1 || !ft_isdigit(*(*str + *i + j))
				|| 0 * j++) && (ft_isalnum(*(*str + *i + j))
				|| *(*str + *i + j) == '_'))
			j++;
		sub = ft_substr(*str, *i + 1, j - 1);
		if (!sub)
			return (-1);
		v = ft_isvarin(sub, ev);
		if (!v)
			v = ft_isvarin(sub, var);
		(void)ft_free(sub);
	}
	if (ft_cut_link(str, ft_substr(*str, 0, *i), v, ft_strdup(*str + *i + j)))
		return (-1);
	*i += ft_varlen(v);
	return (0);
}

int	ft_expvar(char **str, char **ev, char **var)
{
	size_t	i;
	char	dquote;

	i = 0;
	dquote = 0;
	while (*(*str + i))
	{
		if (*(*str + i) == '\'' && !dquote)
			i = ft_skpqts(*str, i);
		else if (*(*str + i) == '\"')
			dquote = (dquote + 1) % 2 + (0 * i++);
		else if (*(*str + i) == '$' && (ft_isalnum(*(*str + i + 1))
				|| *(*str + i + 1) == '_' || *(*str + i + 1) == '?'))
		{
			if (ft_insert(str, &i, ev, var))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
