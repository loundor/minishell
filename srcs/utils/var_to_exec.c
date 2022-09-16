/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:44:22 by stissera          #+#    #+#             */
/*   Updated: 2022/09/16 13:33:33 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_count_index(char **array)
{
	size_t i;

	if (!array)
		return (0);
	
	i = 0;
	while (array[i] && array[i] != NULL)
		i++;
	return (i);
}

static char	*do_line(char *line)
{
	char 	*ret;

	if (*line == '\'')
		ret = take_single_quote(line);
	else
		ret = take_double_quote(line);
	return (ret);
}

char	**var_to_exec(char **av)
{
//	char	**ret;
	size_t	i;

	i = ft_count_index(av);
	if (i == 1)
		return (av);
	while (--i > 0)
		av[i] = do_line(av[i]) + free_str(av[i]);
	av[i] = do_line(av[i]) + free_str(av[i]);
	return (av);
}