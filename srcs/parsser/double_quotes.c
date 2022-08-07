/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:23:10 by stissera          #+#    #+#             */
/*   Updated: 2022/08/07 10:24:27 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -----------------| DOUBLE QUOTES?! |-------------------- */
/*	It's like a simple quotes, but convert var $ with the	*/
/*	right value. For a value need check in struct env and	*/
/*	struct tmp.												*/
/* -------------------------------------------------------- */

char	*take_double_quote(char *param)
{
	char	*line;
	char	*pre;
	char	*reserved;

	line = NULL;
	pre = NULL;
	reserved = NULL;
	param++;
	while (*param && *param != '"' && *param != '\0')
	{
		if (line == NULL)
		{
			line = (char *)malloc(sizeof(char) * 1);
			if (!line)
				exit(ft_exit(MALLOCERR, 2));
			*line = '\0';
		}
		if (*param == '$' && (ft_isalnum(param[1]) || param[1] == '_'))
		{
			pre = take_dollar(param++);
			while ((ft_isalnum(*param) || *param == '_'))
				param++;
			if (pre == NULL)
				continue ;
			if (line != NULL)
			{
				reserved = line;
				line = ft_strjoin(line, pre);
				free(pre);
				free(reserved);
			}
			else
				line = pre;
			continue ;
		}
		pre = line;
		line = ft_joincts(pre, *param++);
		free(pre);
	}
	if (*param == '\0')
	{
		//pre = heredoc(line, 2); // EN ATTENTE DE CREATION DE FONCTION
		free(line);
		return (pre);
	}
	return (line);
}
