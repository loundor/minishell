/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cndcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:43:37 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 02:26:23 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_cndcmp(char **candidate, t_list *tkn)
{
	char	*content;
	size_t	len;

	content = ft_strdup(tkn->content);
	if (!content || ft_remqts(&content))
		return (-1);
	len = ft_strlen(content);
	if (ft_strncmp(*candidate, content, len))
		return (ft_free(content));
	(void)ft_free(content);
	*candidate += len;
	if (!**candidate)
		return (1);
	if (!tkn->next || ft_strncmp(tkn->next->content, "*", 2))
		return (0);
	return (1);
}
