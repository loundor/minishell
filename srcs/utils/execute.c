/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:48:37 by stissera          #+#    #+#             */
/*   Updated: 2022/09/09 15:19:52 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	launch_process(t_tree *tree, char **av, char **ev)
{
	if (tree->parent != NULL && (tree->parent->type == 1
			|| tree->parent->type == 2 || tree->parent->type == 3))
	{
		dup2(tree->parent->fd[0][0], 0);
		dup2(tree->fd[0][1], 1);
		close(tree->parent->fd[0][1]);
	}
	close(tree->fd[0][0]);
	if (tree->cmdr->built != NULL)
		exit (tree->cmdr->built->f(av));
	return (execve(tree->cmdr->command, av, ev));
}

static int	wait_process(t_tree *tree, t_shell *shell)
{
	if (tree->left != NULL)
		if (!wait_process(tree->left, shell))
			return (errno);
	if (tree->right != NULL)
		if (!wait_process(tree->right, shell))
			return (errno);
	if (tree->pid > 0)
		waitpid(tree->pid, &shell->return_err, 0);
	return (0); // Maybe + errno
}

static int	prepare_tree(t_tree *tree)
{
	if (tree->parent == 0)
	{
		if (pipe(tree->fd[0]))
			return (errno);
		//close(tree->parent->fd[0][1]);
	}
	else
	{
/* 	else if (tree->parent->fd[1][0] > 0) // enfant droit
	{
		tree->fd[0][0] = tree->parent->fd[1][0];
		tree->fd[0][1] = tree->parent->fd[1][1];
	}
	else // enfant gauche
	{ */
		tree->fd[0][0] = tree->parent->fd[0][0];
		tree->fd[0][1] = tree->parent->fd[0][1];
	}
	return (0);
}

static int	tree_type_one(t_shell *shell, t_tree *tree)
{
	if (prepare_tree(tree))
		return (errno);
	if (prepare_exec(shell, tree->left))
		return (errno);
	tree->fd[0][0] = tree->left->fd[0][0];
	tree->fd[0][1] = tree->left->fd[0][1];
	if (prepare_exec(shell, tree->right))
		return (errno);
	tree->fd[0][0] = tree->right->fd[0][0];
	tree->fd[0][1] = tree->right->fd[0][1];
	return (0);
}

static int	tree_type_andor(t_shell *shell, t_tree *tree)
{
	if (prepare_tree(tree))
		return (errno);
	if (prepare_exec(shell, tree->left))
		return (errno);
	if (wait_process(tree, shell))
		return (errno);
	tree->fd[0][0] = tree->left->fd[0][0];
	tree->fd[0][1] = tree->left->fd[0][1];
	if (!(shell->return_err != 0 && tree->type == 3)
		|| !(shell->return_err == 0 && tree->type == 2))
		return (0);
	if (prepare_exec(shell, tree->right))
		return (errno);
	tree->fd[0][0] = tree->right->fd[0][0];
	tree->fd[0][1] = tree->right->fd[0][1];
	return (0);
}

static int	tree_type_exe(t_shell *shell, t_tree *tree)
{
	char		**av;
	char		**ev;

	if (pipe(tree->fd[0]) != 0)
		return (errno);
	tree->pid = fork();
	ev = env_to_exec();
	av = param_to_exec(tree->cmdr->param, ft_strdup(tree->cmdr->command));
	if (tree->cmdr->path == NULL)
		tree->cmdr->built = search_builtin(tree->cmdr->command, shell->builtin);
	if (tree->cmdr->built == NULL && tree->cmdr->path == NULL)
		tree->cmdr->command = search_in_path(tree->cmdr->command,
				search_var("PATH") + (0 * free_str(tree->cmdr->command)));
	else
		tree->cmdr->command = ft_strjoin(tree->cmdr->path, tree->cmdr->command)
			+ free_str(tree->cmdr->command);
	if (tree->pid == 0)
		if (!launch_process(tree, av, ev))
			exit (errno);
	if (tree->pid > 0) // && !close(tree->parent->fd[0][1]))
	{
		if (tree->parent != NULL)
			close(tree->parent->fd[0][1]);
		if (tree->parent != 0)
			return (0 + free_tab(av) + free_tab(ev));
	}
	shell->return_err = -1;
	return (errno + free_tab(av) + free_tab(ev));
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
