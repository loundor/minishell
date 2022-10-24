/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:14:34 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 03:51:54 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_list	*ft_lexord(t_list *lst)
{
	t_list	*ord;
	void	*buf;

	ord = lst;
	while (lst && lst->next)
	{
		if (ft_strncmp(lst->content, lst->next->content, (size_t)(-1)) > 0)
		{
			buf = lst->content;
			lst->content = lst->next->content;
			lst->next->content = buf;
			lst = ord;
		}
		else
			lst = lst->next;
	}
	return (ord);
}
