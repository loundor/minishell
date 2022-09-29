/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:22:38 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 15:41:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export(char **par)
{
	size_t	index;

	index = 1;
	if (par[index] == NULL)
		return (0);
	while (par[index] != NULL)
		add_env_line(par[index++]);
	return (0);
}
