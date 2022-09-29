/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:31:49 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 15:32:29 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_type_andor(t_shell *shell, t_tree *tree)
{
	if (prepare_tree(tree))
		return (errno);
	prepare_exec(shell, tree->left);
	waitpid(tree->pid, &shell->return_err, 0);
	tree->fd[0] = tree->left->fd[0];
	tree->fd[1] = tree->left->fd[1];
	if ((shell->return_err != 0 && tree->type == 3)
		|| (shell->return_err == 0 && tree->type == 2))
		return (0);
	prepare_exec(shell, tree->right);
	tree->fd[0] = tree->right->fd[0];
	tree->fd[1] = tree->right->fd[1];
	return (0);
}
