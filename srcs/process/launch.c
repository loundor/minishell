/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:36:46 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:40:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	launch_process(t_tree *tree)
{
	if (tree->parent != NULL && (tree->parent->type == 1
			|| tree->parent->type == 2 || tree->parent->type == 3))
	{
		dup2(tree->parent->fd[0], STDIN_FILENO);
		if (tree->last != 1)
			dup2(tree->fd[1], STDOUT_FILENO);
		close(tree->parent->fd[1]);
	}
	close(tree->fd[0]);
	close(tree->fd[0]);
	if ((tree->cmdr->built == NULL || tree->cmdr->built->f(tree->cmdr->av))
		&& ft_strncmp(tree->cmdr->command, "exit", 5))
		if ((tree->cmdr->command[0] != '.' && tree->cmdr->command[0] != '/')
			|| execve(tree->cmdr->command, tree->cmdr->av, tree->cmdr->ev) == -1)
			exit(127 + (0 * printf("minishell: command not found: %s\n", tree->cmdr->command)));
	exit (1);
}
