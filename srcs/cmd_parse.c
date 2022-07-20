/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/07/20 17:07:02 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ------------------------------------------------------- */
/*              STARTEND[0] = DEPART DU CHAR               */
/*	STARTEND[1] = POSITION DU CHAR TEST ET POSITION DE FIN */
/* ------------------------------------------------------- */
static char	*take_path(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i;
	int		slash;

	i = 0;
	slash = 0;
	while (line[i] != '\0' && !ft_isspace(line[i]))
	{
		if (line[i] == '/')
			slash++;
		i++;
	}
	if (slash > 0)
	{
		while (line[i] != '/')
			i--;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	slash = 0;
	while (slash != i)
		ret[slash++] = *line++;
	ret[slash] = '\0';
	return (ret);
}

static char	*take_exec(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i[2];

	i[0] = 0;
	while (!ft_isspace(line[i[0]]) && line[i[0]] != '\0')
		i[0]++;
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	while (i[1] != i[0])
		ret[i[1]++] = *line++;
	ret[i[1]] = '\0';
	line = ft_skipspace(line);
	return (ret);
}

static char	*take_params(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i[2];

	return (ret);
}

t_cmd	*cmd_parse(char *shell, t_cmd *cmd)
{
	char	*line;
	t_cmd	*new;

	line = shell;
	line = ft_skipspace(line);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!line || !new)
		ft_exit(MALLOCERR, 1);
	new->path = take_path(&line, new);
	line = ft_skipspace(line);
	new->command = take_exec(&line, new);
	line = ft_skipspace(line);
	new->param = take_params(&line, new);
	line = ft_skipspace(line);
	new->option = take_option(&line, new);
	line = ft_skipspace(line);
	new->type = take_operator(&line, new);
	line = ft_skipspace(line);
	if (*line != '\0')
		cmd->next = cmd_parse(line, new);
	return (cmd);
}
