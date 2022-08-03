/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:39:28 by stissera          #+#    #+#             */
/*   Updated: 2022/08/03 22:04:54 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*alloc(int *end, char **ret, char *line)
{
	int	start;

	start = -1;
	ret[0] = (char *)malloc(sizeof(char) * (*end + 1));
	if (!ret[0])
		exit(ft_exit(MALLOCERR, 2));
	while (++start < *end)
		ret[0][start] = *line++;
	ret[0][start] = '\0';
	return (line);
}

static char	*dollar(char *tmp, char *line, char **ret)
{
	tmp = take_dollar(line++);
	while (*line && (ft_isalnum(*line) || *line == '_'))
		line++;
	if (tmp == NULL)
		return (line);
	if (ret[0] != NULL)
		ret[1] = ft_strjoin(ret[0], tmp);
	else
		ret[1] = ft_strdup(tmp);
	if (tmp != NULL)
		free(tmp);
	return (line);
}

static char	*d_quotes(char *tmp, char *line, char **ret)
{
	tmp = take_double_quote(line++);
	while (*line != '\"')
		line++;
	line++;
	if (tmp == NULL)
		return (line);
	if (ret[0] != NULL)
		ret[1] = ft_strjoin(ret[0], tmp);
	else if (tmp != NULL)
		ret[1] = ft_strdup(tmp);
	if (tmp != NULL)
		free(tmp);
	return (line);
}

static char	*s_quotes(char *tmp, char *line, char **ret)
{
	tmp = take_single_quote(line++);
	while (*line != '\'')
		line++;
	line++;
	if (tmp == NULL)
		return (line);
	if (ret[0] != NULL)
		ret[1] = ft_strjoin(ret[0], tmp);
	else
		ret[1] = ft_strdup(tmp);
	if (tmp != NULL)
		free(tmp);
	return (line);
}

static char	*pline(char *tmp, char *line, char **ret)
{
	if (*line == '\'')
		line = s_quotes(tmp, line, ret);
	else if (*line == '\"')
		line = d_quotes(tmp, line, ret);
	else if (*line == '$')
		line = dollar(tmp, line, ret);
	else
		return (line);
	if (ret[1] == NULL)
		return (line);
	if (ret[0] != NULL)
		free (ret[0]);
	ret[0] = ret[1];
	ret[1] = NULL;
	return (line);
}

static char	*maynext(char **ret, char *line, char *tmp)
{
	tmp = line_parse(line);
	if (ret[0] != NULL)
		ret[1] = ft_strjoin(ret[0], tmp);
	else
		ret[1] = ft_strdup(tmp);
	free(tmp);
	if (ret[0] != NULL)
		free (ret[0]);
	ret[0] = ret[1];
	return (ret[0]);
}

char	*line_parse(char *cmd)
{
	char	*line;
	char	*ret[2];
	char	*tmp;
	int		end;

	tmp = NULL;
	ret[0] = NULL;
	ret[1] = NULL;
	line = cmd;
	end = 0;
	while (line[end] != 0 && line[end] != '\'' && line[end] != '"'
		&& !(line[end] == '$' && line[end + 1] != ' '))
		end++;
	if (end != 0)
		line = alloc(&end, ret, line);
	line = pline(tmp, line, ret);
	if (line != NULL && *line != 0)
		ret[0] = maynext(ret, line, tmp);
	return (ret[0]);
}
