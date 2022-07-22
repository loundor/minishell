/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:11:52 by stissera          #+#    #+#             */
/*   Updated: 2022/07/22 13:27:20 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	free_env(shell->env);
	free_cmd(shell->cmd);
	free_builtins(shell->builtin);
	// SEE FOR STRUCT PIPE
}

void	free_env(t_env *env)
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

void	free_env_rec(t_env *env)
{
	int	i;

	i = -1;
	if (env)
	{
		if (env->next_env)
			free_env_rec(env->next_env);
		while (env->env_var[++i])
			free(env->env_var[i]);
		free(env->env_var);
	}
}

void	free_cmd(t_cmd *cmd)
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
			free(cmd->param);
		free(cmd);
	}
}

void	free_builtins(t_builtins *builtins)
{
	if (builtins)
	{
		if (builtins->next)
			free_builtins(builtins->next);
		free(builtins->cmd);
		free(builtins);
	}
}
