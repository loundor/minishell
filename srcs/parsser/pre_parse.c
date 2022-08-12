/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/08/12 20:09:30 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*write_quotes(char *line, char *ret, size_t *i)
{
	if (*line == '"' || *line == '\'')
	{
		if (*line == '"')
		{
			ret[(*i)++] = *line++;
			while (*line != '"')
				ret[(*i)++] = *line++;
		}
		else if (*line == '\'')
		{
			ret[(*i)++] = *line++;
			while (*line != '\'')
				ret[(*i)++] = *line++;
		}
			ret[(*i)++] = *line++;
		if (ret[*i] == '"' || *ret == '\'')
			ret = write_quotes(line, ret, i);
	}
	return (line);
}

static char	*write_parse_space(char *line, size_t i)
{
	char	*ret;

	ret = NULL;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line && *line != 0)
	{
		line = write_quotes(&*line, ret, &i);
		if (*line == ' ')
		{
			ret[i] = *line++;
			while (line && *line == ' ')
				line++;
		}
		else
			ret[i] = *line++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*count_quotes(char *ret, size_t *i)
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

char	*parse_space(char *line)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (*line == '\0')
		return (NULL);
	ret = ft_skipspace(line);
	while (ret && *ret != 0)
	{
		ret = count_quotes(ret, &i);
		if (*ret == ' ')
		{
			i++;
			while (ret && *ret == ' ')
				ret++;
            continue ;
		}
		i++;
		if (ret && *ret == 0)
			break ;
		ret++;
	}
	ret = write_parse_space(ft_skipspace(line), i);
	return (ret);
}
