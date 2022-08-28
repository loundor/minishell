/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:55:12 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 12:40:31 by stissera         ###   ########.fr       */
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
	while (line[size] != '=' && line[size] != 0)
		size++;
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
	size = 0;
	while (line[size] && (line[size] != ' ' || line[size] != '\0'))
		size++;
	var[1] = (char *)malloc(sizeof(char) * (size + 1));
	var[1][size] = 0;
	while (size-- > 0)
		var[1][size] = line[size];
	return (var);
}

void	add_env_line(char *line)
{
	char	**var;
	var = take(line);
	set_env(struct_passing(2, 0), var[1], var[0]);
	free(var);
	return ;
}

void	set_env(t_env *env, char *str, char* type)
{
	while (env->next_env != NULL
		&& ft_strncmp(env->env_var[0], type, ft_strlen(type) + 1))
		env = env->next_env;
	if (env != NULL && !ft_strncmp(env->env_var[0], type, ft_strlen(type) + 1))
	{
		free(env->env_var[1]);
		env->env_var[1] = ft_strdup(str);
		return ;
	}
	add_env_splited(env, str, type);
	return ;
}

void	add_env_splited(t_env *env, char *str, char* type)
{
	t_env	*newenv;
	t_shell	*shell;

	shell = 0;
	newenv = (t_env *)malloc(sizeof(t_env) * 1);
	if (!newenv)
		exit(ft_exit(errno, 1));
	newenv->env_var = (char **)malloc(sizeof(char *) * 2);
	if (!newenv->env_var)
		exit(ft_exit(errno, 1));
	newenv->env_var[0] = ft_strdup(type);
	newenv->env_var[1] = ft_strdup(str);
	newenv->next_env = NULL;
	if (env == 0)
	{
		shell = (t_shell *)struct_passing(1, 0);
		newenv->prev_env = NULL;
		newenv->next_env = NULL;
		shell->env = newenv;
		return ;
	}
	newenv->prev_env = env;
	env->next_env = newenv;
	return ;
}

void rem_env(t_env *env, char *str)
{
	t_shell	*shell;

	shell = 0;
	while (env != NULL && ft_strncmp(env->env_var[0], str, ft_strlen(str) + 1))
		env = env->next_env;
	if (env != NULL && !ft_strncmp(env->env_var[0], str, ft_strlen(str) + 1))
	{
		if (env->prev_env == NULL && env->next_env != NULL)
		{
			shell = (t_shell *)struct_passing(1, 0);
			env->next_env->prev_env = NULL;
			shell->env = env->next_env;
		}
		else if (env->prev_env != NULL && env->next_env == NULL)
		{
			env->prev_env->next_env = NULL;
		}
		else if (env->prev_env == NULL && env->next_env == NULL)
		{
			shell = (t_shell *)struct_passing(1, 0);
			shell->env = NULL;
		}
		else
		{
			env->prev_env->next_env = env->next_env;
			env->next_env->prev_env = env->prev_env;
		}
		free(env->env_var[0]);
		if (env->env_var[1] != NULL)
			free(env->env_var[1]);
		free(env->env_var);	
	}
	return ;
}
