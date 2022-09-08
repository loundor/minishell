/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/09/08 19:02:21 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*count_quotes(char *ret, size_t *i)
{
	if (*ret == '"' || *ret == '\'')
	{
		if (*ret == '"')
		{
			*i = *i + 1;
			while (*++ret != '"')
				*i = *i + 1;
		}
		else if (*ret == '\'')
		{
			*i = *i + 1;
			while (*++ret != '\'')
				*i = *i + 1;
		}
		*i = *i + 1;
		if (*++ret == '"' || *ret == '\'')
			ret = count_quotes(ret, i);
	}
	return (ret);
}

static char	*move_if_type(char *ret, size_t *e)
{
	size_t	i;

	i = *e;
	if (ret[-1] != ' ' && !get_cmd_type(&ret[-1]))
		i++;
	if (get_cmd_type(ret) == 2 || get_cmd_type(ret) == 3
		|| get_cmd_type(ret) == 5 || get_cmd_type(ret) == 7)
	{
		i += 2;
		ret++;
	}
	else
		i++;
	if (*++ret != ' ')
		i++;
	*e = i;
	return (ret);
}

static char	*while_space(char *ret, size_t *i)
{
	while (ret && *ret != 0)
	{
		if (get_cmd_type(ret) || *ret == '(' || *ret == ')')
		{
			ret = move_if_type(ret, &*i);
			continue ;
		}
		ret = count_quotes(ret, &*i);
		if (*ret == ' ')
		{
			*i = *i + 1;
			while (ret && *ret == ' ')
				ret++;
			continue ;
		}
		*i = *i + 1;
		if (ret && *ret == 0)
			break ;
		ret++;
	}
	return (ret);
}

char	*parse_space(char *line)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!line || line == NULL || *line == '\0')
		return (NULL);
	ret = ft_skipspace(line);
	ret = while_space(ret, &i);
	ret = write_parse_space(ft_skipspace(line), i);
	return (ret);
}
