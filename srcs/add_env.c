/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:55:12 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 17:03:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(t_env *env, char *str, char *type)
{
	while (env != NULL && env->next_env != NULL
		&& ft_strncmp(env->env_var[0], type, ft_strlen(type) + 1))
		env = env->next_env;
	if (env != NULL && !ft_strncmp(env->env_var[0], type, ft_strlen(type) + 1))
	{
		free(env->env_var[1]);
		if (str)
			env->env_var[1] = ft_strdup(str);
		else
			env->env_var[1] = NULL;
		return ;
	}
	add_env_splited(env, str, type);
	return ;
}

static void	set_next_prev(t_env *env, t_shell *shell, t_env *newenv)
{
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

void	add_env_splited(t_env *env, char *str, char *type)
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
	if (str)
		newenv->env_var[1] = ft_strdup(str);
	else
		newenv->env_var[1] = NULL;
	newenv->next_env = NULL;
	set_next_prev(env, shell, newenv);
	return ;
}

static void	set_env_rem(t_env *env, t_shell *shell)
{
	if (env->prev_env == NULL && env->next_env != NULL)
	{
		shell = (t_shell *)struct_passing(1, 0);
		env->next_env->prev_env = NULL;
		shell->env = env->next_env;
	}
	else if (env->prev_env != NULL && env->next_env == NULL)
		env->prev_env->next_env = NULL;
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
	return ;
}

void	rem_env(t_env *env, char *str)
{
	t_shell	*shell;

	shell = 0;
	if (!str || str == 0)
		return ;
	while (env != NULL && ft_strncmp(env->env_var[0], str, ft_strlen(str) + 1))
		env = env->next_env;
	if (env != NULL && !ft_strncmp(env->env_var[0], str, ft_strlen(str) + 1))
		set_env_rem(env, shell);
	free(env->env_var[0]);
	free(env->env_var[1]);
	free(env->env_var);
	free(env);
	return ;
}
