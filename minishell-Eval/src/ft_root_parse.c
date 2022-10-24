/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_root_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:09:04 by alfux             #+#    #+#             */
/*   Updated: 2022/09/13 16:16:13 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_varsze(char *arg, size_t *i, char **ev, char	**var)
{
	size_t	size;
	int		j;

	j = 0 * (*i)++;
	while (*(ev + j))
	{
		size = 0;
		while (*(*(ev + j) + size) && *(*(ev + j) + size) != '=')
			size++;
		if (!ft_strncmp(arg + *i, *(ev + j), size) && *(arg + *i + size) != '_'
			&& !ft_isalnum(*(arg + *i + size)))
		{
			*i += size - 1;
			return (ft_strlen(*(ev + j) + size + 1));
		}
		j++;
	}
	if (var)
	{
		(*i)--;
		return (ft_varsze(arg, i, var, (char **)0));
	}
	while (ft_isalnum(*(arg + *i + 1)) || *(arg + *i + 1) == '_')
		(*i)++;
	return (0);
}

static int	ft_newsze(char *arg, char **ev, char **var)
{
	size_t	size;
	size_t	i;
	char	quotes;
	char	dquotes;

	size = 0;
	i = 0;
	quotes = 0;
	dquotes = 0;
	while (*(arg + i))
	{
		if (!dquotes && *(arg + i) == 39)
			quotes = (quotes + 1) % 2;
		else if (!quotes && *(arg + i) == 34)
			dquotes = (dquotes + 1) % 2;
		else if (ev && var && *(arg + i) == '$' && (ft_isalnum(*(arg + i + 1))
				|| *(arg + i + 1) == '_' || *(arg + i + 1) == '?') && !quotes)
			size += ft_varsze(arg, &i, ev, var);
		else
			size++;
		i++;
	}
	return (size);
}

static void	ft_fill_var(char **dst, char **src, char **ev, char **var)
{
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	while (*(ev + i))
	{
		size = 0;
		while (*(*(ev + i) + size) && *(*(ev + i) + size) != '=')
			size++;
		if (!ft_strncmp(*src, *(ev + i), size) && !ft_isalnum(*(*src + size))
			&& *(*src + size) != '_')
		{
			*src += size - 1;
			j = 1;
			while (*(*(ev + i) + size + j))
				*((*dst)++) = *(*(ev + i) + size + j++);
			return ;
		}
		i++;
	}
	if (var)
		return (ft_fill_var(dst, src, var, (char **)0));
	while (ft_isalnum(*(*src + 1)) || *(*src + 1) == '_')
		(*src)++;
}

static void	ft_replace(char *dst, char *src, char **ev, char **var)
{
	char	quotes;
	char	dquotes;

	quotes = 0;
	dquotes = 0;
	while (*src)
	{
		if (*src == 39 && !dquotes)
			quotes = (quotes + 1) % 2;
		else if (*src == 34 && !quotes)
			dquotes = (dquotes + 1) % 2;
		else if (ev && var && !quotes && *src == '$' && (ft_isalnum(*(src + 1))
				|| *(src + 1) == '_' || *(src + 1) == '?'))
		{
			src++;
			ft_fill_var(&dst, &src, ev, var);
		}
		else
			*(dst++) = *src;
		src++;
	}
}

int	ft_root_parse(char **cmd, char **ev, char **var)
{
	size_t	new_size;
	char	*buf;
	int		i;

	i = 0;
	if (!cmd)
		return (ft_errno(EINVAL));
	while (*(cmd + i))
	{
		new_size = ft_newsze(*(cmd + i), ev, var);
		buf = ft_calloc(new_size + 1, sizeof (char));
		if (!buf)
			return (errno);
		ft_replace(buf, *(cmd + i), ev, var);
		(void)ft_free(*(cmd + i));
		*(cmd + i) = buf;
		i++;
	}
	return (0);
}
