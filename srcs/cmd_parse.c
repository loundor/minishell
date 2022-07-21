/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/07/21 13:25:25 by stissera         ###   ########.fr       */
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
	size_t	slash;

	i = 0;
	slash = 0;
	while (line[i] != '\0' && !ft_isspace(line[i]))
	{
		if (line[i] == '/')
			slash++;
		i++;
	}
	if (slash == 0)
		return (line);
	if (slash > 0)
		while (line[i] != '/')
			i--;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	slash = 0;
	while (slash <= i)
		ret[slash++] = *line++;
	ret[slash + 1] = '\0';
	cmd->path = ret;
	return (line);
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
	i[1] = 0;
	while (i[1] <= i[0])
		ret[i[1]++] = *line++;
	ret[i[1] + 1] = '\0';
	line = ft_skipspace(line);
	cmd->command = ret;
	line = ft_skipspace(line);
	return (line);
}

static char	*take_params(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i[2];

	i[0] = 0;
	if (!line || *line == '\0')
		return (0);
	while (line[i[0]] != '\0' && line[i[0]] != '|' && (line[i[0]] != '&'
			&& line[i[0] + 1] != '&') && line[i[0]] != '>' && line[i[0]] != '<')
		i[0]++;
	if (i[0] == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	i[1] = 0;
	while (i[1] < i[0])
		ret[i[1]++] = *line++;
	ret[i[1] + 1] = '\0';
//	cmd->param = check_quote(ret, struct_passing(1, 0));
	cmd->param = ret; // to check
	line = ft_skipspace(line);
	return (line);
}

static char	*take_operator(char *line, t_cmd *cmd)
{
	if (!line || *line == '\0')
		return (NULL);
	if (!ft_strncmp(line, "||", 2))
		cmd->type = 2;
	else if (!ft_strncmp(line, "|", 1))
		cmd->type = 1;
	if (!ft_strncmp(line, "&&", 2))
		cmd->type = 3;
	if (!ft_strncmp(line, "<<", 2))
		cmd->type = 7;
	else if (!ft_strncmp(line, "<", 1))
		cmd->type = 6;
	if (!ft_strncmp(line, ">>", 2))
		cmd->type = 5;
	else if (!ft_strncmp(line, ">", 1))
		cmd->type = 4;
	if (cmd->type == 5 || cmd->type == 7 || cmd->type == 2 || cmd->type == 3)
		line += 2;
	else
		line++;
	line = ft_skipspace(line);
	return (line);
}

t_cmd	*cmd_parse(char *shell, t_cmd *cmd)
{
	char	*line;
	t_cmd	*new;

	line = shell;
	(void)cmd;
	line = ft_skipspace(line);
	new = malloc(sizeof(t_cmd));
	if (!line || !new)
		ft_exit(MALLOCERR, 1);
	line = take_path(line, new);
	line = ft_skipspace(line);
	line = take_exec(line, new);
	line = take_params(line, new);
	line = take_operator(line, new);
	if (line && *line != '\0')
		new->next = cmd_parse(line, new);
	return (new);
}
