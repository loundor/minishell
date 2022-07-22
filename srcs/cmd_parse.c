/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/07/22 14:07:13 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -----------------| PARSSE THE DIRECTORY |--------------- */
/*	Take the line until a space and come back to the last / */
/*	if no / in the line before a space, PATH = NULL			*/
/*	For the future, when path is NULL, check in env $PATH	*/
/*	The pointer of line variable was moved until the end of */
/*	path.													*/
/* -------------------------------------------------------- */
static char	*take_path(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i;
	size_t	slash;

	if (*line == '\"')
		return (line);
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

/* ------------------| PARSSE THE FILE |------------------- */
/*	After try to catch a path, we get the reste of the line */
/*	We juste catch the start of line until a space and put	*/
/*	that in a variable command stored in struct cmd and		*/
/*	return the reste of the line.							*/
/* -------------------------------------------------------- */
static char	*take_exec(char *line, t_cmd *cmd)
{
	char	*ret;
	t_cmd	more;
	size_t	i[2];

	i[0] = 0;
	if (*line == '\"')
	{
		line++;
		while (line[i[0]] != '\"')
			i[0]++;
	}
	else
		while (!ft_isspace(line[i[0]]) && line[i[0]] != '\0')
			i[0]++;
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	i[1] = 0;
	while (i[1] < i[0])
		ret[i[1]++] = *line++;
	ret[i[1] + 1] = '\0';
	if (*line == '\"')
		line++;
	if (*line == '\"')
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

/* ----------------| PARSSE THE PARAMETER |---------------- */
/*	The line start after the command. Also we take the rest */
/*	until a \0, redirection, pipe and binary test.			 */
/* -------------------------------------------------------- */
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
		return (line);
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	i[1] = 0;
	while (i[1] < i[0])
		ret[i[1]++] = *line++;
	ret[i[1]] = '\0';
//	cmd->param = check_quote(ret, struct_passing(1, 0));
	cmd->param = ret; // to check
	line = ft_skipspace(line);
	return (line);
}

/* --------------| PARSSE BETWEEN COMMAND |---------------- */
/*	We check the rest of the line. If the line egal \0 that	*/
/*	means the command is finish otherise we put the			*/
/*	variable to TYPE in struct to know what the redirection */
/*	pipe, or binary operation is.							*/
/* -------------------------------------------------------- */
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

/* ------------------| START OF PARSER |------------------- */
/*	The parser work in recurssive mode when the line is		*/
/*	empty after parssing. When the line containt something	*/
/*	we create a new structure cmd to place the new command.	*/
/*	See struct in minishell.h								*/
/* -------------------------------------------------------- */
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
	if (new->param != NULL)
		new->param = param_parse(new);
	line = take_operator(line, new);
	if (line && *line != '\0')
	{
		new->next = cmd_parse(line, new);
		new->next->prev = new;
	}
	return (new);
}
