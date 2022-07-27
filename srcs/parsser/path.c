/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:31:26 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 16:32:03 by stissera         ###   ########.fr       */
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
	char	*ret;
	size_t	i;
	size_t	slash;

	cmd->path = NULL;
	if (!line || *line == '\"')
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
	ret = (char *)malloc(sizeof(char) * (i + 2));
	if (!ret)
		ft_exit(MALLOCERR, 1);
	slash = 0;
	while (slash <= i)
		ret[slash++] = *line++;
	ret[slash] = '\0';
	cmd->path = ret;
	return (line);
}
