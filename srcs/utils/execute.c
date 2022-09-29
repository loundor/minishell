/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:48:37 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:45:09 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_all_fd(t_tree *tree)
{
	if (tree->left != NULL)
		if (close_all_fd(tree->left))
			return (errno);
	if (tree->right != NULL)
		if (close_all_fd(tree->right))
			return (errno);
	if (tree->fd[0] != 0 || tree->fd[1] != 0)
	{
		close(tree->fd[0]);
		close(tree->fd[1]);
	}
	dup2(1, STDOUT_FILENO);
	dup2(0, STDIN_FILENO);
	return (0);
}
