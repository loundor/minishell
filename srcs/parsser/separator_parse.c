/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:17:48 by stissera          #+#    #+#             */
/*   Updated: 2022/08/10 09:59:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*separator_parse(char *line)
{
	char	*ret;
	char	*bak;
	size_t	i;
	int		type;

	ret = NULL;
	bak = NULL;
	i = 0;
	bak = (char *)malloc(sizeof(char) * (i * 1);
	if (!ret)
		exit(ft_exit(MALLOCERR, 1));
	while (line && *line != 0 && !get_cmd_type(line))
	{
		if (ret && *ret == 0)
		{
			bak[i++] = *line++;
			bak[i] = 0;
		}
		else
		{
			bak[i++] = ft_joincts(ret, *line++);
			free(ret);
		}
		ret = bak;
		i++;
	}
	if (get_cmd_type(line) || *line == '(' || *line == ')' && line[-1] != 32)
	{
		bak = ret;
		ret = ft_joincts(bak, ' ');
		free(bak);
		if ()
		{
			bak = ret;
			ret = ft_joincts(bak, ' ');
			free(bak);
		}
	}
	else
	{
			
	}

	return (ret);
}
