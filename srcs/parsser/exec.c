/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:32:29 by stissera          #+#    #+#             */
/*   Updated: 2022/08/03 22:11:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ------------------| PARSSE THE FILE |------------------- */
/*	After try to catch a path, we get the reste of the line */
/*	We juste catch the start of line until a space and put	*/
/*	that in a variable command stored in struct cmd and		*/
/*	return the reste of the line.							*/
/* -------------------------------------------------------- */

char	*take_exec(char *line, t_cmd *cmd)
{
	char	*ret;
	size_t	i[2];

	i[0] = 0;
	while (!ft_isspace(line[i[0]]) && line[i[0]] != '\0'
		&& line[i[0]] != '\'' && line[i[0]] != '"') // ADD || && << >> < >...
		i[0]++;
	ret = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!ret)
		exit(ft_exit(MALLOCERR, 2));
	i[1] = 0;
	while (i[1] < i[0])
		ret[i[1]++] = *line++;
	ret[i[1]] = '\0';
	line = ft_skipspace(line);
	cmd->command = ret;
	return (line);
}
