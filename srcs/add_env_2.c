/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:01:44 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 15:58:54 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**take_value(char **var, char *line)
{
	size_t	size;

	size = 0;
	while (line[size] && (line[size] != ' ' || line[size] != '\0'))
		size++;
	var[1] = (char *)malloc(sizeof(char) * (size + 1));
	var[1][size] = 0;
	while (size-- > 0)
		var[1][size] = line[size];
	return (var);
}

static char	**take(char *line)
{
	size_t	size;
	char	**var;

	size = 0;
	while (line[size] != '=' && line[size] != 0)
		size++;
	if (*line == '$' || size == ft_strlen(line))
		return (NULL + ( 0 * printf("Can't create the environnement variable.\n")));
	var = (char **)malloc(sizeof(char *) * 2);
	var[0] = (char *)malloc(sizeof(char) * (size + 1));
	if (!var[0])
		exit(ft_exit(errno, 1));
	var[0][size] = 0;
	while (size-- > 0)
		var[0][size] = line[size];
	while (*line != '=' && *line != 0)
		line++;
	if (*line == 0)
	{
		var[1] = NULL;
		return (var);
	}
	line++;
	return (take_value(var, line));
}

void	add_env_line(char *line)
{
	char	**var;

	if (!line || line == NULL)
		return ;
	var = take(line);
	set_env(struct_passing(2, 0), var[1], var[0]);
	free(var[0]);
	free(var[1]);
	free(var);
	return ;
}
