/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:23:10 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 17:02:25 by stissera         ###   ########.fr       */
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
	size_t	count;
	size_t	start;
	char	*line;
	char	*new;

	count = 0;
	start = -1;
	line = NULL;
	new = NULL;
	param++;
	if (param == NULL)
		return (NULL);	// For test but NEED sent to HEREDOC!
	while (param[count] != '"' && (param[count] == '$'
			&& param[count + 1] != ' ') && param[count] != '\0')
		count++;
	if (*param)
		return (NULL);	// For test but NEED sent to HEREDOC!
	line = (char *)malloc(sizeof(char) * (count + 1));
	if (!line)
		exit(ft_exit(MALLOCERR, 2));
	while (++start <= count)
		line[start] = *param++;
	line[count] = '\0';
	if (*param != '\0')
		new = take_double_quote(line);
	if (new != NULL)
	{
		free (line);
		line = new;
	}
	return (line);
}
