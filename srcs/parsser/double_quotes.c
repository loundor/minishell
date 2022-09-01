/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:23:10 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 10:47:21 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -----------------| DOUBLE QUOTES?! |-------------------- */
/*	It's like a simple quotes, but convert var $ with the	*/
/*	right value. For a value need check in struct env and	*/
/*	struct tmp.												*/
/* -------------------------------------------------------- */
/*	NE GERE PAS LE HEREDOC DOUBLE QUOTE!					*/
/* -------------------------------------------------------- */

static char	*is_null_line(char *line)
{
	if (line == NULL)
	{
		line = (char *)malloc(sizeof(char) * 1);
		if (!line)
			exit(ft_exit(MALLOCERR, 2));
		*line = '\0';
	}
	return (line);
}

static char	*after_dollar_null(char *line, char *pre)
{
	char	*reserved;

	reserved = NULL;
	if (line != NULL)
	{
		reserved = line;
		line = ft_strjoin(line, pre);
		free(pre);
		free(reserved);
	}
	else
		line = pre;
	return (line);
}

char	*take_double_quote(char *param)
{
	char	*line;
	char	*pre;

	line = NULL;
	pre = NULL;
	param++;
	while (*param && *param != '"' && *param != '\0')
	{
		line = is_null_line(line);
		if (*param == '$' && (ft_isalnum(param[1]) || param[1] == '_'))
		{
			pre = take_dollar(param++);
			while ((ft_isalnum(*param) || *param == '_'))
				param++;
			if (pre == NULL)
				continue ;
			line = after_dollar_null(line, pre);
			continue ;
		}
		pre = line;
		line = ft_joincts(pre, *param++);
		free(pre);
	}
	return (line);
}
