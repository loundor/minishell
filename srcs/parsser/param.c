/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:33:11 by stissera          #+#    #+#             */
/*   Updated: 2022/08/30 15:23:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ----------------| PARSSE THE PARAMETER |---------------- */
/*	The line start after the command. Also we take the rest */
/*	until a \0, redirection, pipe and binary test.			 */
/* -------------------------------------------------------- */
char	*take_params(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i[2];

	i[0] = 0;
	cmd->param = NULL;
	if (!line || *line == '\0')
		return (NULL);
	while (line[i[0]] != '\0')
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
	cmd->param = ret;
	line = ft_skipspace(line);
	return (line);
}
