/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:31:26 by stissera          #+#    #+#             */
/*   Updated: 2022/08/03 22:09:50 by stissera         ###   ########.fr       */
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

char	*take_path(char *line, t_cmd *cmd)
{
	size_t	i;
	size_t	slash;

	cmd->path = NULL;
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
