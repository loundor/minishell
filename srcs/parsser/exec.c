/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:32:29 by stissera          #+#    #+#             */
/*   Updated: 2022/08/02 15:00:01 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ------------------| PARSSE THE FILE |------------------- */
/*	After try to catch a path, we get the reste of the line */
/*	We juste catch the start of line until a space and put	*/
/*	that in a variable command stored in struct cmd and		*/
/*	return the reste of the line.							*/
/* -------------------------------------------------------- */


// MAUVAISE IDEE!!!
static char	*test_env(char	*param)
{
	char	*line;
	char	*pre;
	char	*reserved;
	size_t	i;

	i = -1;
	while (param[++i] != '\0')
	{
		if (*param == '$' && (ft_isalnum(param[1]) || param[1] == '_'))
		{
			pre = take_dollar(param++);
			if (line != NULL)
			{
				reserved = line;
				line = ft_strjoin(line, pre);
				free(pre);
				free(reserved);
			}
			else
				line = pre;
			while ((ft_isalnum(*param) || *param == '_'))
				param++;
			continue ;
		}
	}
	return (ret);
}

char	*take_exec(char *line, t_cmd *cmd)
{
	char	*ret;
	t_cmd	more;
	size_t	i[2];
	char	type_quote;

	i[0] = 0;
	if (*line == '"' || *line == '\'')
	{
		type_quote = *line;
		line++;
		while (line[i[0]] != type_quote)
			i[0]++;
	}
	else
		while (!ft_isspace(line[i[0]]) && line[i[0]] != '\0'
			&& line[i[0]] != '\'' && line[i[0]] != '"')
			i[0]++;
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		exit(ft_exit(MALLOCERR, 2));
	i[1] = 0;
	while (i[1] < i[0])
		ret[i[1]++] = *line++;
	ret[i[1]] = '\0';
	if (*line == type_quote && *line != '\0')
		line++;
	if (line && (*line == '"' || *line == '\'' || (*line > 32 && *line < 126)))
	{
		line = take_exec(line, &more);
		cmd->command = ft_strjoin(ret, more.command);
		free(more.command);
		return (line);
	}
	line = ft_skipspace(line);
	cmd->command = ret;
	return (line);
}
