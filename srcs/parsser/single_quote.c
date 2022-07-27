/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:22:21 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 16:24:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ------------------|	SINGLE QUOTE |--------------------- */
/*	Take the line until a single quote and return that in a */
/*	malloced variable. If end of line without single quote	*/
/*	open a HEREDOC to finish the right line.				*/
/*	HEREDOC NO ALLREADY IMPLEMENTED!!!!!					*/
/* -------------------------------------------------------- */
char	*take_single_quote(char *param)
{
	char	*line;
	size_t	start;
	size_t	stop;
	int		space;

	start = -1;
	space = 1;
	stop = 0;
	line = ++param;
	while (line[stop] != '\'')
		stop++;
	if (line[stop + 1] == ' ')
		space = 2;
	line = (char *)malloc(sizeof(char) * stop + 2);
	if (!line)
		exit(ft_exit(MALLOCERR, 2));
	while (++start < stop)
		line[start] = *param++;
	if (space == 2)
		line[start++] = 32;
	line[start] = '\0';
	return (line);
}
