/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:53:32 by stissera          #+#    #+#             */
/*   Updated: 2022/08/26 15:00:49 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_bt(t_tree *tree)
{
	if (tree->left && tree->left != NULL)
		free_bt(tree->left);
	if (tree->right && tree->right != NULL)
		free_bt(tree->right);
	if (tree->cmd && tree->cmd != NULL)
		free_cmd(tree->cmd);
	free(tree);
}
