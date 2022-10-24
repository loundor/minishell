/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wldprep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:14:36 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 05:04:15 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_addblk(t_list **tkn, char *blk)
{
	t_list	*new;

	if (blk)
	{
		new = ft_lstnew(blk);
		if (new)
		{
			ft_lstadd_back(tkn, new);
			return (0);
		}
		(void)ft_free(blk);
	}
	ft_lstclear(tkn, (void (*)(void *))(&ft_free));
	return (1);
}

static t_list	*ft_wldtkn(char *ptrn)
{
	t_list	*tkn;
	size_t	i;

	tkn = (t_list *)0;
	if (!*ptrn)
		(void)ft_addblk(&tkn, ft_strdup(ptrn));
	while (*ptrn)
	{
		i = 0;
		while (*(ptrn + i) && *(ptrn + i) != '*' && *(ptrn + i) != '/')
		{
			if (*(ptrn + i) == '\'' || *(ptrn + i) == '\"')
				i = ft_skpqts(ptrn, i);
			else
				i++;
		}
		if (i && ft_addblk(&tkn, ft_substr(ptrn, 0, i)))
			return ((t_list *)0);
		if ((*(ptrn + i) == '*' && ft_addblk(&tkn, ft_strdup("*")))
			|| (*(ptrn + i) == '/' && ft_addblk(&tkn, ft_strdup("/"))))
			return ((t_list *)0);
		ptrn += i + !!*(ptrn + i);
	}
	return (tkn);
}

static int	ft_isempty(char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) != '\'' && *(str + i) != '\"')
			return (0);
		else if (*(str + i) == '\"' && *(str + i + 1) != '\"')
			return (0);
		else if (*(str + i) == '\'' && *(str + i + 1) != '\'')
			return (0);
		else
			i += 2;
	}
	return (1);
}

static t_list	*ft_rem_mty_tkn(t_list *tkn, int go)
{
	t_list	*nav;
	t_list	*buf;

	if (!tkn || !go)
		return (tkn);
	nav = tkn;
	while (nav && ft_isempty((char *)nav->content))
	{
		tkn = nav->next;
		ft_lstdelone(nav, (void (*)(void *))(&ft_free));
		nav = tkn;
	}
	while (nav && nav->next)
	{
		if (ft_isempty((char *)nav->next->content))
		{
			buf = nav->next;
			nav->next = nav->next->next;
			ft_lstdelone(buf, (void (*)(void *))(&ft_free));
		}
		else
			nav = nav->next;
	}
	return (tkn);
}

t_list	*ft_wldprep(char *pattern, char **ev, char **var)
{
	t_list	*wldtkn;
	size_t	i;
	int		go;

	if (!pattern)
		return ((t_list *)(size_t)(0 * ft_errno(EINVAL)));
	pattern = ft_strdup(pattern);
	i = 0;
	go = 0;
	if (!pattern || ft_expvar(&pattern, ev, var))
		return ((t_list *)(size_t)ft_free(pattern));
	wldtkn = (t_list *)0;
	while (*(pattern + i) && !go)
	{
		if (*(pattern + i) == '\"' || *(pattern + i) == '\'')
			i = ft_skpqts(pattern, i) - 1;
		else if (*(pattern + i) == '*')
			go = 1;
		i++;
	}
	if (go)
		wldtkn = ft_wldtkn(pattern);
	else if (ft_addblk(&wldtkn, ft_strdup(pattern)))
		return ((t_list *)(size_t)ft_free(pattern));
	return (ft_rem_mty_tkn(wldtkn, go + ft_free(pattern)));
}
