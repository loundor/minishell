/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:10:47 by stissera          #+#    #+#             */
/*   Updated: 2022/09/02 14:16:14 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_exec(t_shell *shell, t_tree * tree)
{
	if (tree->left != NULL)
		prepare_exec(shell, tree->left);
	if (tree->type == 0 && tree->parent == NULL)
	{
		exec_single(tree);
		return (0);
	}
	else if (tree->type == 1)
	{
		if (tree->right->type == 0)
		{
			if (pipe(tree->pipe) == 0)
			{
				//add change signal or before de prepare_exec
				tree->pid = fork();
				if (tree->pid < 0)
					return (ft_exit(errno, 1));
				else if (tree->pid == 0)
				{
					close(tree->pipe[1]);
					execve(ft_strjoin(tree->left->cmdr->path, tree->left->cmdr->command), tree->left->cmdr->param, env_to_exec()); // leaks created!
					return (ft_exit(errno, 1));
				}
				close(tree->pipe[1]);


			}
		}
	}
	else if (tree->type == 2)
	{

	}
	else if (tree->type == 3)
	{

	}
	else if (tree->type == 4 || tree->type == 5)
	{
		if (pipe(tree->pipe) == 0)
		{
			if 	(tree->parent->pipe[1] != 0)
				tree->pipe[0] = tree->parent->pipe[1];
			else
				tree->pipe[0] = STDOUT;
		}
	}
	else if (tree->type == 6 || tree->type == 7)
	{

	}
	return (0);
}
