/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:29:19 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:41:00 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	tree_prep_exe(t_shell *shell, t_tree *tree, char *path)
{
	tree->cmdr->ev = env_to_exec();
	var_to_exec(tree->cmdr);
	tree->cmdr->av = param_to_exec(tree->cmdr->param, tree->cmdr->command);
	if (tree->cmdr->path == NULL)
		tree->cmdr->built = search_builtin(tree->cmdr->command, shell->builtin);
	if (tree->cmdr->built == NULL && tree->cmdr->path == NULL)
	{
		path = search_in_path(tree->cmdr->command, search_var("PATH"));
		if (path && path != NULL)
			tree->cmdr->command = path + free_str(tree->cmdr->command);
	}
	else if (tree->cmdr->built == NULL)
		tree->cmdr->command = ft_strjoin(tree->cmdr->path, tree->cmdr->command);
	if (tree->last == 1 && tree->cmdr->built != NULL)
	{
		shell->return_err = tree->cmdr->built->f(tree->cmdr->av);
		if (tree->parent != NULL)
		{
			tree->parent->pid = 0;
			return (1 * close(tree->parent->fd[1]));
		}
		if (tree->parent == 0)
			return (1);
	}
	return (0);
}

int	tree_type_exe(t_shell *shell, t_tree *tree)
{
	char	*path;

	if (pipe(tree->fd) != 0)
		return (errno);
	path = NULL;
	if (tree_prep_exe(shell, tree, path))
		return (errno || 0);
	setsig(1);
	tree->pid = fork();
	if (tree->pid == 0)
		if (!launch_process(tree))
			exit (errno);
	if (tree->pid > 0)
	{
		if (tree->parent != NULL)
		{
			tree->parent->pid = tree->pid;
			return (0 * close(tree->parent->fd[1]
					+ close(tree->parent->fd[0])));
		}
		if (tree->parent == 0)
			return (0);
	}
	shell->return_err = -1;
	return (errno);
}
