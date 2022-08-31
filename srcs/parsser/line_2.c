/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:34:51 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 00:35:41 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*alloc(int *end, char **ret, char *line)
{
	int	start;

	start = -1;
	ret[0] = (char *)malloc(sizeof(char) * (*end + 1));
	if (!ret[0])
		exit(ft_exit(MALLOCERR, 2));
	while (++start < *end)
		ret[0][start] = *line++;
	ret[0][start] = '\0';
	return (line);
}

char	*dollar(char *tmp, char *line, char **ret)
{
	tmp = take_dollar(line++);
	while (*line && (ft_isalnum(*line) || *line == '_' || *line == '?'))
		line++;
	while (*line == ' ')
		line++;
	if (tmp == NULL)
		return (line);
	if (ret[0] != NULL)
		ret[1] = ft_strjoin(ret[0], tmp);
	else
		ret[1] = ft_strdup(tmp);
	if (tmp != NULL)
		free(tmp);
	return (line);
}
