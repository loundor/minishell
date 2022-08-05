/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:22:21 by stissera          #+#    #+#             */
/*   Updated: 2022/08/04 14:23:05 by stissera         ###   ########.fr       */
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
	char	*pre;

	line = NULL;
	pre = NULL;
	line = (char *)malloc(sizeof(char) * 2);
	if (!line)
		exit(ft_exit(MALLOCERR, 2));
	*line = *param++;
	line[1] = '\0';
	while (*param && *param != '\'' && *param != '\0')
	{
		pre = line;
		line = ft_joincts(pre, *param++);
		free(pre);
	}
	if (*param == '\0')
	{
		//pre = heredoc(line); // EN ATTENTE DE CREATION DE FONCTION
		free(line);
		return (pre);
	}
	pre = line;
	line = ft_joincts(pre, '\'');
	free(pre);
	return (line);
}
