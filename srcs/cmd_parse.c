/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/07/21 11:56:42 by stissera         ###   ########.fr       */
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
	{
		cmd->path = NULL;
		return (line);
	}
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
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	i[1] = 0;
	while (i[1] < i[0])
		ret[i[1]++] = *line++;
	ret[i[1] + 1] = '\0';
//	cmd->param = check_quote(ret, struct_passing(1, 0));
	cmd->param = ret; // to check
	return (line);
}

static char	*take_operator(char *line, t_cmd *cmd)
{
	int		ret;
//	size_t	i[2];

cmd->type = 1;
	if (!line || *line == '\0')
		return (0);
	ret = 0;
	(void)line;
	return (line);
}

t_cmd	*cmd_parse(char *shell, t_cmd *cmd)
{
	char	*line;
	t_cmd	*new;

	line = shell;
printf("\nSTART = %s", line);
	line = ft_skipspace(line);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!line || !new)
		ft_exit(MALLOCERR, 1);
	line = take_path(line, new);
printf("\nPATH = %s", new->path);
	line = ft_skipspace(line);
	line = take_exec(line, new);
printf("\nEXEC = %s", new->command);
	line = ft_skipspace(line);
	line = take_params(line, new);
printf("\nPARAM = %s", new->param);
	line = ft_skipspace(line);
	line = take_operator(line, new);
printf("\nTYPE = %d", new->type);
	line = ft_skipspace(line);
	if (line && *line != '\0')
{
printf("\nTAKE NEXT CMD");
		cmd->next = cmd_parse(line, new);
}
printf("FINISH");
	return (cmd);
}
