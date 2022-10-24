/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cndstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:46:57 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 01:23:07 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_cndstr(char **cnd, t_list *tkn)
{
	char	*match;
	char	*content;

	content = ft_strdup(tkn->content);
	if (!content || ft_remqts(&content))
		return (-1);
	match = ft_strnstr(*cnd, content, ft_strlen(*cnd));
	if (!match)
		return (ft_free(content));
	*cnd = match + ft_strlen(content);
	return (1 + ft_free(content));
}
