/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:44:28 by alfux             #+#    #+#             */
/*   Updated: 2022/09/27 02:33:56 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_addblk(t_list **tmp, void *blk)
{
	t_list	*new;

	if (!blk)
	{
		ft_lstclear(tmp, (void (*)(void *))(&ft_free));
		return (1);
	}
	new = ft_lstnew(blk);
	if (!new)
	{
		ft_lstclear(tmp, (void (*)(void *))(&ft_free));
		ft_free(blk);
		return (1);
	}
	ft_lstadd_back(tmp, new);
	return (0);
}

static char	**ft_lst_to_tab(t_list *lst)
{
	size_t	size;
	t_list	*buf;
	char	**tokens;
	int		i;

	size = ft_lstsize(lst);
	if (size < 2147483647)
	{
		tokens = ft_calloc(size + 1, sizeof (char *));
		if (tokens)
		{
			i = 0;
			buf = lst;
			while (buf)
			{
				*(tokens + i++) = buf->content;
				buf = buf->next;
			}
			ft_lstclear(&lst, (void (*)(void *))0);
			return (tokens);
		}
	}
	ft_lstclear(&lst, (void (*)(void *))(&ft_free));
	return ((char **)0);
}

static int	ft_septkn(t_list **tmp, char *pmt, size_t *i)
{
	if (*(pmt + *i + 1) == *(pmt + *i))
	{
		if (ft_addblk(tmp, ft_substr(pmt, *i, 2)))
			return (1);
		(*i)++;
	}
	else if (ft_addblk(tmp, ft_substr(pmt, *i, 1)))
		return (1);
	(*i)++;
	return (0);
}

static int	ft_wrdtkn(t_list **tmp, char *pmt, size_t *i, char ***null)
{
	size_t	j;
	char	err;

	j = *i;
	while (*(pmt + *i) && !ft_istokn(pmt + *i) && *(pmt + *i) != ' ')
	{
		if (*(pmt + *i) == 39 || *(pmt + *i) == 34)
		{
			err = *(pmt + *i);
			*i = ft_skpqts(pmt, *i);
			if (!*i)
			{
				ft_lstclear(tmp, (void (*)(void *))(&ft_free));
				*null = ft_calloc(1, sizeof (char *));
				ft_errmsg((-1 * (err == 39)) + (-2 * (err == 34)));
				return (1);
			}
		}
		else
			(*i)++;
	}
	if (ft_addblk(tmp, ft_substr(pmt, j, *i - j)))
		return (1);
	return (0);
}

char	**ft_tknize(char *pmt)
{
	size_t	i;
	char	**null;
	t_list	*tmp;

	i = 0;
	tmp = (t_list *)0;
	null = (char **)0;
	while (*(pmt + i))
	{
		i = ft_skpspc(pmt, i);
		if (ft_istokn(pmt + i) == 2)
		{
			if (ft_addblk(&tmp, ft_substr(pmt, i++, 1)))
				return (null);
		}
		else if (ft_istokn(pmt + i) == 1)
		{
			if (ft_septkn(&tmp, pmt, &i))
				return (null);
		}
		else if (*(pmt + i))
			if (ft_wrdtkn(&tmp, pmt, &i, &null))
				return (null);
	}
	return (ft_lst_to_tab(tmp));
}
