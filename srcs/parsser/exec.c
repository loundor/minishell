/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:32:29 by stissera          #+#    #+#             */
/*   Updated: 2022/08/31 17:30:05 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ------------------| PARSSE THE FILE |------------------- */
/*	After try to catch a path, we get the reste of the line */
/*	We juste catch the start of line until a space and put	*/
/*	that in a variable command stored in struct cmd and		*/
/*	return the reste of the line.							*/
/* -------------------------------------------------------- */

static size_t	count_char(char *line)
{
	size_t	i;

	i = 0;
	while (line && line[i] != '\0' && !ft_isspace(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (line[i] == '\'')
			{
				i++;
				while (line && line[i] != '\0' && line[i] != '\'')
					i++;
			}
			if (line && line[i] != '\0' && line[i] == '"')
			{
				i++;
				while (line && line[i] != '\0' && line[i] != '"')
					i++;
			}
			continue ;
		}
		i++;
	}
	return (i);
}

char	*take_exec(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	e;
	size_t	i;

	i = count_char(line);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		exit(ft_exit(MALLOCERR, 2));
	e = 0;
	while (e < i)
		ret[e++] = *line++;
	ret[e] = '\0';
	line = ft_skipspace(line);
	cmd->command = ret;
	return (line);
}
