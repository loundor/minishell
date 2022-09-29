/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:34:28 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:40:56 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_type_one(t_shell *shell, t_tree *tree)
{
	if (prepare_tree(tree))
		return (errno);
	if (prepare_exec(shell, tree->left))
		return (errno);
	tree->fd[0] = tree->left->fd[0];
	tree->fd[1] = tree->left->fd[1];
	if (prepare_exec(shell, tree->right))
		return (errno);
	tree->fd[0] = tree->right->fd[0];
	tree->fd[1] = tree->right->fd[1];
	return (0);
}
