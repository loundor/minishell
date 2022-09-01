/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:31:26 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 10:20:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -----------------| PARSSE THE DIRECTORY |--------------- */
/*	Take the line until a space and come back to the last / */
/*	if no / in the line before a space, PATH = NULL			*/
/*	For the future, when path is NULL, check in env $PATH	*/
/*	The pointer of line variable was moved until the end of */
/*	path.													*/
/* -------------------------------------------------------- */

static char	*take_path_write(t_cmd *cmd, size_t i, size_t slash, char *line)
{
	while (line[i] != '/')
		i--;
	cmd->path = (char *)malloc(sizeof(char) * (i + 2));
	if (!cmd->path)
		ft_exit(MALLOCERR, 1);
	slash = 0;
	while (slash <= i)
		cmd->path[slash++] = *line++;
	cmd->path[slash] = '\0';
	return (line);
}

char	*take_path(char *line, t_cmd *cmd)
{
	size_t	i;
	size_t	slash;
	int		jump_char[2];

	cmd->path = NULL;
	jump_char[0] = -1;
	jump_char[1] = -1;
	i = 0;
	slash = 0;
	while ((line[i] != '\0' && !ft_isspace(line[i]))
		|| (!jump_char[0] && !jump_char[1]))
	{
		if (line[i] == '\'')
			jump_char[0] *= -1;
		if (line[i] == '\"')
			jump_char[1] *= -1;
		if (line[i] == '/')
			slash++;
		i++;
	}
	if (slash == 0)
		return (line);
	line = take_path_write(cmd, i, slash, line);
	return (line);
}
