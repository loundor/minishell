/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skptkn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:01:52 by alfux             #+#    #+#             */
/*   Updated: 2022/09/29 22:05:06 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_list	*ft_skptkn(t_list *lst, char const *tkn)
{
	size_t	len;

	len = ft_strlen(tkn);
	while (lst && !ft_strncmp((char const *)lst->content, tkn, len + 1))
		lst = lst->next;
	return (lst);
}
