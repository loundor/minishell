/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:11:52 by stissera          #+#    #+#             */
/*   Updated: 2022/09/20 09:43:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_tab(char **t)
{
	int	i;

	i = -1;
	while (t[++i] != NULL)
		free(t[i]);
	free(t);
	return (0);
}

int	free_str(char *str)
{
	if (str)
		free(str);
	return (0);
}

int	free_shell(t_shell *shell)
{
	if (shell->line != NULL)
		free(shell->line);
	if (shell->env != NULL)
		free_env(shell->env);
	if (shell->builtin != NULL)
		free_builtins(shell->builtin);
	if (shell->tree && shell->tree != NULL)
		free_bt(shell->tree);
	return (0);
}

int	free_env(t_env *env)
{
	int	i;

	i = -1;
	if (env != NULL)
	{
		if (env->next_env)
			free_env(env->next_env);
		while (env->env_var[++i] != NULL)
			free(env->env_var[i]);
		free(env->env_var);
		free(env);
	}
	return (0);
}

int	free_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		if (cmd->path != NULL)
			free(cmd->path);
		if (cmd->command != NULL)
			free(cmd->command);
		if (cmd->param != NULL)
			free(cmd->param);
		if (cmd->ev != NULL)
			free_tab(cmd->ev);
		if (cmd->av != NULL)
			free_tab(cmd->av);
		cmd->built = NULL;
		free(cmd);
	}
	return (0);
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
