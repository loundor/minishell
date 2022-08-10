/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/08/11 00:13:02 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*write_quotes(char *line, char *ret, size_t *i)
{
	if (*ret == '"' || *ret == '\'')
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
		if (*++ret == '"' || *ret == '\'')
			ret = write_quotes(line, ret, i);
	}
	return (ret);
}

static char	*write_parse_space(char *line, size_t i)
{
	char	*ret;

	ret = NULL;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line && *line != 0)
	{
		ret = write_quotes(line, ret, &i);
		if (*line == ' ')
		{
			ret[i] = *line++;
			while (*line == ' ')
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
			i++;
			while (*++ret != '"')
				i++;
		}
		else if (*ret == '\'')
		{
			i++;
			while (*++ret != '\'')
				i++;
		}
		i++;
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
		}
		i++;
		if (ret && *ret == 0)
			break ;
		ret++;
	}
	if (ret[-1] && ret[-1] == ' ')
		i--;
	ret = write_parse_space(ft_skipspace(line), i);
	return (ret);
}
