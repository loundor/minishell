/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:17:06 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 15:31:34 by stissera         ###   ########.fr       */
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
			{
				ret[(*i)++] = *line++;
			}
		}
		else if (*line == '\'')
		{
			ret[(*i)++] = *line++;
			while (*line != '\'')
			{
				ret[(*i)++] = *line++;
				*i = *i + 1;
			}
		}
			ret[(*i)++] = *line++;
		if (*line == '"' || *line == '\'')
			line = write_quotes(line, ret, i);
	}
	return (line);
}

static char	*write_is_space(char *ret, char *line, size_t i)
{
	ret[i] = *line++;
	while (line && *line == ' ')
		line++;
	return (line);
}

static char	*write_is_sep(char *ret, char *line, size_t *i)
{
	if (line[-1] != ' ' && !get_cmd_type(&line[-1]))
	{
		ret[*i] = ' ';
		*i = *i + 1;
	}
	if (get_cmd_type(line) == 2 || get_cmd_type(line) == 3
		|| get_cmd_type(line) == 5 || get_cmd_type(line) == 7)
	{
		ret[*i] = *line++;
		*i = *i + 1;
	}
	ret[*i] = *line++;
	*i = *i + 1;
	if (*line != ' ')
	{
		ret[*i] = ' ';
		*i = *i + 1;
	}
	return (line);
}

char	*write_parse_space(char *line, size_t i)
{
	char	*ret;

	ret = NULL;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line && *line != 0)
	{
		if (get_cmd_type(line) || *line == '(' || *line == ')')
		{
			line = write_is_sep(ret, &*line, &i);
			continue ;
		}
		line = write_quotes(&*line, ret, &i);
		if (*line == ' ')
			line = write_is_space(&*ret, &*line, i);
		else if (*line == 0)
			continue ;
		else
			ret[i] = *line++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
