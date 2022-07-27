/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:23:54 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 16:24:06 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* --------------| WITH $VAR TO ENV VAR |------------------ */
/*	Take the variable (until space, no alphanum caractere	*/
/*	or _) and call the function search_var to get the var	*/
/*	if var don't exist, we get en NULL return				*/
/*	TAKE CARE ABOUT THE SPACE AFTER THE $VAR!!!! need impl.	*/
/* -------------------------------------------------------- */
char	*take_dollar(char *param)
{
	char	*line;
	char	*search;
	size_t	start;
	size_t	end;
	int		c;

	start = -1;
	end = 0;
	param++;
	while (param[end] != 0 && (ft_isalnum(param[end]) || param[end] == '_'))
		end++;
	if (param[end] == 32)
		c = 2;
	search = (char *)malloc(sizeof(char) * (end + 1));
	if (!search)
		exit(ft_exit(MALLOCERR, 1));
	while (++start < end)
		search[start] = *(param++);
	search[start] = 0;
	line = search_var(search);
	if (line != NULL)
		free(search);
	if (c && c == 2)
	{
		search = ft_strjoin(line, " ");
		free (line);
		line = search;
	}
	return (line);
}
