/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:00:26 by stissera          #+#    #+#             */
/*   Updated: 2022/07/22 11:34:23 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_shell(t_shell *shell)
{

}

static void	free_env(t_env *env)
{
	if (env)
	{
		if (env->prev_env)
		{
			env->prev_env->next_env = NULL;
			env->prev_env = NULL;
		}
		free_env_rec(env);
	}
}

static void free_env_rec(t_env *env)
{
	if (env)
	{
		if (env->next)
			free_env_rec(env->next);
		
	}
}
static void free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->next)
			free_cmd(cmd->next);
		if (cmd->path)
			free(cmd->path);
		if (cmd->command)
			free(cmd->command);
		if (cmd->param)
			free(param);
		free(cmd);
	}
}

static void free_builtins(t_builtins *builtins)
{
	if (builtins)
	{
		if (builtins->next)
			free_builtins(builtins->next);
		free(builtins->cmd);
		free(builtins);
	}
}

static void	err_type(int msg, void *data)
{
	if (msg == 1)
		free((t_env *)data);
	if (msg == 2)
	{
		err_type(1, (t_shell *)data);
		free ((t_builtins *)((t_shell *)data)->builtin);
	}
}

/* ------------| NEED EXIT??! PREVENT LEAKS! |------------- */
/*	The function tale a type of "error" and put a message	*/
/*	in a screen. If there are something to free (level)		*/
/*	We call the err_type with the code/level to free and	*/
/*	exit the program without leaks.							*/
/*	TO_FREE= 0-Nothing; 1-SHELL; 2-ENV; 3-CMD; 4-BUILTINS	*/
/* -------------------------------------------------------- */
int	ft_exit(int type, int to_free)
{
	if (type == 1)
		printf("Can't create environement structure!");
	else if (type == 2)
		printf("Malloc error!");
	else if (type == 3)
		printf("Welcome error!");
	else if (type == 4)
		printf("No environement variable!");
	else if (type == 5)
		printf("Signal modification not autorized");
	else if (type == 6)
		printf("Can't create builtins!");
	else if (type == 7)
	{
		printf("Error command not found!\n");
		return (1);
	}
	if (to_free)
		err_type(to_free, struct_passing(to_free, 0));
	return (0);
}
