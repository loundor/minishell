/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:52:08 by alfux             #+#    #+#             */
/*   Updated: 2022/09/06 18:00:29 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_init_var(void)
{
	char	**var;

	var = ft_calloc(2, sizeof (char *));
	if (!var)
		return ((char **)0);
	*var = ft_strdup("?=0");
	if (!*var)
		return ((char **)(size_t)ft_free(var));
	return (var);
}
