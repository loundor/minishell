/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:10:47 by stissera          #+#    #+#             */
/*   Updated: 2022/09/02 09:37:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_exec(t_shell *shell, t_tree * tree)
{
	if (tree->left != NULL)
	{
		prepare_exec(shell, tree);
		
	}
	return (0);
}
