/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/08/30 12:37:46 by stissera         ###   ########.fr       */
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
		if (get_cmd_type(line) || *line == '(' || *line == ')')
		{
			if (line[-1] != ' ' && !get_cmd_type(&line[-1]))
				ret[i++] = ' ';
			if (get_cmd_type(line) == 2 || get_cmd_type(line) == 3
				|| get_cmd_type(line) == 5 || get_cmd_type(line) == 7)
			{
				ret[i++] = *line++;
			}
			ret[i++] = *line++;
			if (*line != ' ')
				ret[i++] = ' ';
			continue ;
		}
		line = write_quotes(&*line, ret, &i);
		if (*line == ' ')
		{
			ret[i] = *line++;
			while (line && *line == ' ')
				line++;
		}
		else if (*line == 0)
			continue ;
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
	if (!line || line == NULL || *line == '\0')
		return (NULL);
	ret = ft_skipspace(line);
	while (ret && *ret != 0)
	{
		if (get_cmd_type(ret) || *ret == '(' || *ret == ')')
		{
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
			ret++;
			if (*ret != ' ')
				i++;
			continue ;
		}
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
