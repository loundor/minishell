/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:33:31 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:40:57 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_tree(t_tree *tree)
{
	if (tree->parent != 0 && tree->parent->fd[1] != 0)
	{
		tree->fd[0] = tree->parent->fd[0];
		tree->fd[1] = tree->parent->fd[1];
	}
	return (0);
}

int	pre_prepare_exec(t_shell *shell, t_tree *tree)
{
	if (tree->type == 2 || tree->type == 3)
	{
		if (pre_prepare_exec(shell, tree->left))
			return (errno);
		if (wait_process(tree, shell))
			return (errno);
		tree->fd[0] = tree->left->fd[0];
		tree->fd[1] = tree->left->fd[1];
		if ((shell->return_err != 0 && tree->type == 3)
			|| (shell->return_err == 0 && tree->type == 2))
			return (0);
		if (pre_prepare_exec(shell, tree->right))
			return (errno);
		tree->fd[0] = tree->right->fd[0];
		tree->fd[1] = tree->right->fd[1];
	}
	else
		if (prepare_exec(shell, tree))
			return (errno);
	return (0);
}

int	prepare_exec(t_shell *shell, t_tree *tree)
{
	if (tree->type == 1 && tree_type_one(shell, tree))
		return (errno);
	if ((tree->type == 2 || tree->type == 3) && tree_type_andor(shell, tree))
		return (errno);
	if (tree->type == 0 && tree_type_exe(shell, tree))
		return (errno);
	return (0);
}
