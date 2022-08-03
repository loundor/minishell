/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:35:56 by stissera          #+#    #+#             */
/*   Updated: 2022/08/02 15:29:44 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ---------------| PARAMETER PARSSING |------------------- */
/*	Get the pointer of cmd->param. Of every caractere check	*/
/*	if it's a signle or double quote and launch the funct	*/
/*	if need. Recept the new created line, and free the last	*/
/*	linenbak 0 -> parssing str								*/
/*	linenbak 1 -> str to parsse								*/
/*				/!\ REWRITE THE EXPLAIN BLOCK!!!			*/
/* -------------------------------------------------------- */

char	*param_parse(char *cmd)
{
	char	*line;
	char	*ret[2];
	char	*tmp;
	size_t	start;
	size_t	end;

	tmp = NULL;
	ret[0] = NULL;
	start = -1;
	line = cmd;
	end = 0;
	while (line[end] != 0 && line[end] != 39 && line[end] != 34
		&& !(line[end] == 36 && line[end + 1] != 32))
		end++;
	if (end == ft_strlen(line))
		return (cmd);
	if (end != 0)
	{
		ret[0] = (char *)malloc(sizeof(char) * (end + 1));
		if (!ret[0])
			exit(ft_exit(MALLOCERR, 2));
		while (++start < end)
			ret[0][start] = *line++;
		ret[0][start] = '\0';
	}
	if (*line == '\'')
	{
		tmp = take_single_quote(line);
		if (ret[0] != NULL)
		{
			ret[1] = ft_strjoin(ret[0], tmp);
			free(tmp);
		}
		else
			ret[1] = tmp;
		while (*(++line) != '\'');
		line++;
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
	}
	else if (*line == '\"')
	{
		tmp = take_double_quote(line);
		if (ret[0] != NULL)
		{
			ret[1] = ft_strjoin(ret[0], tmp);
			free(tmp);
		}
		else
			ret[1] = tmp;
		while (*(++line) != '\"');
		line++;
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
	}
	else if (*line == '$')
	{
		tmp = take_dollar(line);
		if (ret[0] != NULL && tmp != NULL)
		{
			ret[1] = ft_strjoin(ret[0], tmp);
			free(tmp);
		}
		else if (ret[0] != NULL && tmp == NULL)
			ret[1] = ft_strdup(ret[0]);
		else if (ret[0] == NULL && tmp != NULL)
			ret[1] = tmp;
		else
			ret[1] = 0;
		while (*(++line) != '\0' && (ft_isalnum(*line) || *line == '_'));
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
	}
	if (line != NULL && *line != 0)
	{
		line = ft_skipspace(line);
		tmp = param_parse(line);
		if (ret[0] != NULL)
			ret[1] = ft_strjoin(ret[0], tmp);
		else
			ret[1] = ft_strdup(tmp);
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
	}
	return (ret[0]);
}
