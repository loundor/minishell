/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:11:52 by stissera          #+#    #+#             */
/*   Updated: 2022/08/30 20:55:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->line != NULL)
		free(shell->line);
	free_env(shell->env);
	free_builtins(shell->builtin);
	free_bt(shell->tree);
}

void	free_env(t_env *env)
{
	int	i;

	i = -1;
	if (env != NULL)
	{
		if (env->next_env)
			free_env(env->next_env);
		while (env->env_var[++i])
			free(env->env_var[i]);
		free(env->env_var);
		free(env);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
//		if (cmd->next != NULL)
//			free_cmd(cmd->next);
		if (cmd->path != NULL)
			free(cmd->path);
		if (cmd->command != NULL)
			free(cmd->command);
		if (cmd->param != NULL)
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

void	free_bt(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		free_bt((t_tree *)tree->left);
	if (tree->right && tree->right != NULL)
		free_bt((t_tree *)tree->right);
	if (tree->cmdr && tree->cmdr != NULL)
		free_cmd((t_cmd *)tree->cmdr);
	if (tree->cmd && tree->cmd != NULL)
		free(tree->cmd);
	free(tree);
}
