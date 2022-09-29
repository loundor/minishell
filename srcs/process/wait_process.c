/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:43:47 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:43:57 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_process(t_tree *tree, t_shell *shell)
{
	if (tree->left != NULL)
		if (wait_process(tree->left, shell))
			return (errno);
	if (tree->right != NULL)
		if (wait_process(tree->right, shell))
			return (errno);
	if (tree->pid > 0)
		waitpid(tree->pid, &shell->return_err, 0);
	return (0);
}
