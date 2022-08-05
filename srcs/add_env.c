/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:55:12 by stissera          #+#    #+#             */
/*   Updated: 2022/08/05 13:04:02 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**take(char *line)
{
	size_t	size;
	char	**var;

	size = 0;
	if (*line == '$')
		line++;
	while (line[size] != '=')
		size++;
	var = (char **)malloc(sizeof(char *) * 2);
	var[0] = (char *)malloc(sizeof(char) * (size + 1));
	if (!var[0])
		exit(ft_exit(MALLOCERR, 1));
	var[0][size] = 0;
	while (size-- > 0)
		var[0][size] = line[size];
	while (*line != '=')
		line++;
	line++;
	size = 0;
	while (line[size] && (line[size] != ' ' || line[size] != '\0'))
		size++;
	var[1] = (char *)malloc(sizeof(char) * (size + 1));
	var[1][size] = 0;
	while (size-- > 0)
		var[1][size] = line[size];
	return (var);
}

int	add_env(char *line)
{
	t_env	*env;
	t_env	*add;
	char	**var;

	var = take(line);
	env = (t_env *)struct_passing(2, 0);
	add = (t_env *)malloc(sizeof(t_env));
	if (!add)
		exit(ft_exit(MALLOCERR, 1));
	while (env->next_env != NULL)
		env = env->next_env;
	add->env_var = var;
	add->next_env = NULL;
	env->next_env = add;
	add->prev_env = env;
	return (0);
}
