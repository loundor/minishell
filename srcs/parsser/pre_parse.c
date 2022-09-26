/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/09/26 18:34:38 by stissera         ###   ########.fr       */
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

static char	*write_quotes(char *line, size_t *i, char *ret)
{
	char	*bak;
	char	quotes;

	quotes = line[*i];
	bak = NULL;
	ret = ft_joincts(bak, line[*i]);
	*i = *i + 1;
	while (line[*i] != 0 && ft_strncmp(&line[*i], &quotes, 1))
	{
		bak = ret;
		ret = ft_joincts(bak, line[*i]) + free_str(bak);
		*i = *i + 1;
	}
	bak = ret;
	ret = ft_joincts(bak, line[*i]) + free_str(bak);
	*i = *i + 1;
	return (ret);
}

static char	*write_type(char *line, size_t *i, char *ret)
{
	char	*bak;

	bak = NULL;
	ret = ft_joincts(ret, line[*i]);
	*i = *i + 1;
	if (line[*i] != 0 && !ft_strncmp(&line[*i - 1], &line[*i], 1)
		&& (ft_strncmp(&line[*i - 1], "(", 1)
			|| ft_strncmp(&line[*i - 1], ")", 1)))
	{
		bak = ret;
		ret = ft_joincts(bak, line[*i]) + free_str(bak);
		*i = *i + 1;
	}
	bak = ret;
	ret = ft_joincts(bak, ' ') + free_str(bak);
	return (ret);
}

char	*parse_space(char *line)
{
	char	*ret;
	char	*bak;
	char	*sep;
	size_t	i;

	i = 0;
	sep = NULL;
	ret = NULL;
	bak = NULL;
	while (line && line[i] != 0)
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (ret)
				bak = ret;
			sep = write_quotes(line, &i, ret);
			if (bak)
				ret = ft_strjoin(bak, sep) + free_str(bak) + free_str(sep);
			else
				ret = ft_strdup(sep) + free_str(bak) + free_str(sep);
		}
		else if (line[i] == '>' || line[i] == '<'
			|| line[i] == '|' || line[i] == '&'
			|| line[i] == '(' || line[i] == ')')
		{
			if (ret)
			{
				if (ret[ft_strlen(ret) - 1] != ' ')
					bak = ft_joincts(ret, ' ') + free_str(ret);
				else
					bak = ft_strdup(ret) + free_str(ret);
				ret = bak;
			}
			ret = write_type(line, &i, ret) + free_str(bak);
		}
		else
		{
			if (ret)
				bak = ret;
			ret = ft_joincts(bak, line[i++]) + free_str(bak);
		}
		if (line != 0 && line[i] == ' ' && ret[ft_strlen(ret) - 1] != ' ')
		{
			if (ret)
				bak = ret;
			ret = ft_joincts(bak, ' ') + free_str(bak);
		}
		if (line[i] != 0 && line[i] == ' ')
			while (line[i] == ' ')
				i++;
	}
	return (ret);
}
