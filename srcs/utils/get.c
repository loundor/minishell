/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:57:32 by stissera          #+#    #+#             */
/*   Updated: 2022/08/08 09:29:47 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd_type(char *line)
{
	int	ret;

	ret = 0;
	if (*line == '|' && line[1] != '|')
		ret = 1;
	else if (*line == '|' && line[1] == '|')
		ret = 2;
	else if (*line == '&' && line[1] == '&')
		ret = 3;
	else if (*line == '>' && line[1] != '>')
		ret = 4;
	else if (*line == '>' && line[1] == '>')
		ret = 5;
	else if (*line == '<' && line[1] != '<')
		ret = 6;
	else if (*line == '<' && line[1] == '<')
		ret = 7;
	return (ret);
}