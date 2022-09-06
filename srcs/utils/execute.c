/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:10:47 by stissera          #+#    #+#             */
/*   Updated: 2022/09/06 18:39:18 by stissera         ###   ########.fr       */
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
	if (tree->type == 1)
	{
		if (tree->parent != NULL && tree->parent->fd[0] != 0)
		{
			tree->fd[0] = tree->parent->fd[0];
			tree->fd[1] = tree->parent->fd[1];
		}
		else
			pipe(tree->fd);
		prepare_exec(shell, tree->left);
		tree->code_err = tree->left->code_err;
		close(tree->fd[0]);
		close(tree->fd[1]);
		tree->fd[0] = tree->left->fd[0];
		tree->fd[1] = tree->left->fd[1];
		prepare_exec(shell, tree->right);
		tree->code_err = tree->right->code_err;
		dup2(tree->fd[0], tree->right->fd[0]);
		dup2(tree->fd[1], tree->right->fd[1]);
		//tree->fd[0] = tree->right->fd[0];
		//tree->fd[1] = tree->right->fd[1];
		return (0);
	}

	else if (tree->type == 0)
	{
//		char	*av[2];
		char	**ev;
		char	*cmd;

		pipe(tree->fd);
		ev = env_to_exec();
/* 		av = arg_to_exec(); // need to implement */
/* 		if (tree->cmdr->path == NULL)
			// test builtins
			cmd = search_in_path(tree->cmdr->command);
		else */
			cmd = ft_strjoin(tree->cmdr->path, tree->cmdr->command);
		if ((tree->pid = fork()) == 0)
		{
			if (tree->parent != NULL && tree->parent->type == 1)
			{
				dup2(tree->fd[1], 1);
				dup2(tree->parent->fd[0], 0);
				close(tree->fd[0]);
				close(tree->fd[1]);
				close(tree->parent->fd[0]);
				close(tree->parent->fd[1]);
			}
//			if (execve(cmd, (char* const*)av, ev == -1))
			if (execve(cmd, (char * const*)tree->cmdr->param, ev))
				tree->code_err = 127;
			return (127);
		}
		free(ev);
		free(cmd);
	}
	return (0);
}
