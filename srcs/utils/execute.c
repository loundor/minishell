/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:10:47 by stissera          #+#    #+#             */
/*   Updated: 2022/09/05 22:43:53 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_exec(t_shell *shell, t_tree *tree)
{
	char **env;
	char *cmd;

	(void)shell;
	tree->pid = fork();
	if (tree->pid == 0)
	{
		// Child process
		if (tree->parent != NULL)
		{
			dup2(tree->parent->fd[1],1);
			close(tree->parent->fd[1]);
			if (getpid() == tree->parent->right->pid)
				dup2(tree->parent->fd[0], 0);
			close(tree->parent->fd[0]);
		}
		//do changesignal
		env = env_to_exec();
//		if (tree->cmdr->path == NULL)
//			cmd = search_in_path(tree->cmdr->command);
//		else
			cmd = ft_strjoin(tree->cmdr->path, tree->cmdr->command);
		execve(cmd, (char * const*)tree->cmdr->param, env);
	}
	close(tree->parent->fd[0]);
	close(tree->parent->fd[1]);
}

int	prepare_exec(t_shell *shell, t_tree * tree)
{
	if (tree->type == 2 || tree->type == 3)
	{
		if (tree->left == NULL || tree->right == NULL)
		{
			tree->code_err = 2;
			return (2);
		}
		if (pipe(tree->fd) < 0)
			return (ft_exit(errno, 1));
		if (tree->left != NULL)
			return (1);
		prepare_exec(shell, tree->left);
		waitpid(-1, &tree->code_err, 0);
		if ((tree->type == 2 && tree->code_err != 0)
			|| (tree->type == 3 && tree->code_err == 0))
			prepare_exec(shell, tree->right);
		waitpid(-1, &tree->code_err, 0);
		return (0);
	}
	else if (tree->type == 1)
	{
		if (tree->left == NULL || tree->right == NULL)
		{
			tree->code_err = 2;
			return (2);
		}
		if (tree->left == NULL || tree->right == NULL)
			return (1);
		if (tree->parent != NULL)
		{
			tree->fd[0] = tree->parent->fd[0];
			tree->fd[1] = tree->parent->fd[1];
		}
		else
			pipe(tree->fd);
		prepare_exec(shell, tree->left);
		prepare_exec(shell, tree->right);
	}

	else if ((tree->type == 4) | (tree->type == 5)) // > or >>
	{
		if (pipe(tree->fd) < 0)
			return (ft_exit(errno, 1));
		if (tree->type == 4)
			tree->fd[1] = open(tree->right->cmdr->command, O_CREAT , 0700);
		if (tree->type == 5)
			tree->fd[1] = open(tree->right->cmdr->command, O_APPEND | O_CREAT, 0700);
		//exec_redir_out(shell, tree);
		// return executuin in tree->code_err
	}
	else if (tree->type == 6) // <
	{
		if (pipe(tree->fd) < 0)
			return (ft_exit(errno, 1));
		tree->fd[0] = open(tree->right->cmdr->command, O_RDONLY);
		//exec_redir_in(shell, tree);
	}
	if (tree->type == 0)
		do_exec(shell, tree); // before exec check if parent->right->pid == getpid of child if yes dup2(parent->fd[1], 1);
	return (0);
}
