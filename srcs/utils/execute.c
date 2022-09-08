/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:10:47 by stissera          #+#    #+#             */
/*   Updated: 2022/09/08 23:04:00 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_exec(t_shell *shell, t_tree * tree)
{
	if (tree->type == 1)
	{
		if (tree->parent == NULL)
		{
			write(1, "PARENT!\n\0", 9);
			pipe(tree->fd[0]);
			prepare_exec(shell, tree->left);
		}
		else
		{
			if (tree->parent->fd[2][0] > 0)
			{
				write(1, "FD2>0!\n\0", 8);
				tree->fd[0][0] = tree->parent->fd[2][0];
				tree->fd[0][1] = tree->parent->fd[2][1];
				prepare_exec(shell, tree->left);
			}
			else if (tree->parent->fd[1][0] > 0)
			{
				write(1, "FD1>0!\n\0", 8);
				tree->fd[0][0] = tree->parent->fd[1][0];
				tree->fd[0][1] = tree->parent->fd[1][1];
				prepare_exec(shell, tree->left);
			}
			else
			{
				write(1, "FD1=0!\n\0", 8);
				tree->fd[0][0] = tree->parent->fd[0][0];
				tree->fd[0][1] = tree->parent->fd[0][1];
				prepare_exec(shell, tree->left);
			}
		}
		if (tree->left->type == 1 || tree->left->type == 2
			|| tree->left->type == 3)
		{
			tree->fd[1][0] = tree->left->fd[2][0];
			tree->fd[1][1] = tree->left->fd[2][1];
		}
		else
		{
			tree->fd[1][0] = tree->left->fd[1][0];
			tree->fd[1][1] = tree->left->fd[1][1];
		}
		
		if (tree->left->type == 0)
			printf("PIDL %d ------\n", tree->left->pid);
		//printf("RETURN ERR LEFT %d ------\n", tree->code_err);

		prepare_exec(shell, tree->right);
		tree->fd[2][0] = tree->right->fd[2][0];
		tree->fd[2][1] = tree->right->fd[2][1];
/* 		{
			close(tree->left->fd[0][0]);
			close(tree->left->fd[0][1]);
		} */
		if (tree->right->type == 0)
			printf("PIDR %d ------\n", tree->right->pid);
		// close(tree->right->fd[2][1]);
		//waitpid(tree->right->pid, &tree->code_err, WNOHANG);
/* 		{
			close(tree->right->fd[1][0]);
			close(tree->right->fd[1][1]);
		} */
		//printf("RETURN ERR RIGHT %d ------\n", tree->code_err);
		close(tree->fd[0][0]);
		close(tree->fd[0][1]);
		close(tree->fd[1][0]);
		close(tree->fd[1][1]);
		return (0);
	}
	
	else if (tree->type == 2 || tree->type == 3)
	{
		if (tree->parent == NULL)
		{
			write(1, "PARENT!\n\0", 9);
			pipe(tree->fd[0]);
			prepare_exec(shell, tree->left);
		}
		else
		{
			if (tree->parent->fd[2][0] > 0)
			{
				write(1, "FD2>0!\n\0", 8);
				tree->fd[0][0] = tree->parent->fd[2][0];
				tree->fd[0][0] = tree->parent->fd[2][0];
				prepare_exec(shell, tree->left);
			}
			else if (tree->parent->fd[1][0] > 0)
			{
				write(1, "FD1>0!\n\0", 8);
				tree->fd[0][0] = tree->parent->fd[1][0];
				tree->fd[0][1] = tree->parent->fd[1][1];
				prepare_exec(shell, tree->left);
			}
			else
			{
				write(1, "FD1=0!\n\0", 8);
				tree->fd[0][0] = tree->parent->fd[0][0];
				tree->fd[0][1] = tree->parent->fd[0][1];
				prepare_exec(shell, tree->left);
			}
		}
		waitpid(tree->left->pid, &tree->code_err, 0);
		tree->code_err = tree->left->code_err;
		if (tree->left->type == 1 || tree->left->type == 2 || tree->left->type == 3)
		{
			tree->fd[1][0] = tree->left->fd[2][0];
			tree->fd[1][1] = tree->left->fd[2][1];
		}
		else
		{
		tree->fd[1][0] = tree->left->fd[1][0];
		tree->fd[1][1] = tree->left->fd[1][1];
		}
		if ((tree->code_err != 0 && tree->type == 3)
			|| (tree->code_err == 0 && tree->type == 2))
		{
			if (tree->left->type == 0)
				printf("PIDL OR/AND %d ------\n", tree->left->pid);
			prepare_exec(shell, tree->right);
			tree->fd[2][0] = tree->right->fd[2][0];
			tree->fd[2][1] = tree->right->fd[2][1];
			if (tree->right->type == 0)
				printf("PIDR %d ------\n", tree->right->pid);
			waitpid(tree->right->pid, &tree->code_err, WNOHANG);
		}
		else
		{
			tree->fd[2][0] = tree->left->fd[1][0];
			tree->fd[2][1] = tree->left->fd[1][1];
		}
		return (0);
	}

	/* IN TO A NEW FUNCTION */
	else if (tree->type == 0)
	{
		char	**av;
		char	**ev;
		char	*cmd;
		t_builtins	*builtin;

		builtin = NULL;
		if (tree->parent != NULL && tree->parent->type == 1)
		{
			if (tree->parent->fd[1][0] > 0)
				pipe(tree->fd[2]);
			else
				pipe(tree->fd[1]);
		}
		else
			pipe(tree->parent->fd[2]);
		ev = env_to_exec();
 		av = param_to_exec(tree->cmdr->param);
		av[0] = ft_strdup(tree->cmdr->command);
		cmd = NULL;
 		if (tree->cmdr->path == NULL)
			builtin = search_builtin(tree->cmdr->command, shell->builtin);
		if (builtin == NULL && tree->cmdr->path == NULL)
			cmd = search_in_path(tree->cmdr->command, search_var("PATH"));
		if (builtin == NULL && cmd != NULL && (tree->pid = fork()) == 0)
		{
			if (tree->parent != NULL && (tree->parent->type == 1
					|| tree->parent->type == 2 || tree->parent->type == 3))
			{
				/* IN TO A NEW FUNCTION */
				if (tree->fd[2][0] > 0)
				{
					dup2(tree->parent->fd[1][0], 0);
					dup2(tree->fd[2][1], 1);
					//tree->parent->fd[1][0] = dup(0);
					//tree->fd[2][1] = dup(1);
					
					close(tree->parent->fd[1][0]);
					close(tree->parent->fd[1][1]);
					close(tree->fd[2][0]);
					close(tree->fd[2][1]);
				}
				else
				{
					dup2(tree->parent->fd[0][0], 0); // pb on strin if on
					dup2(tree->fd[1][1], 1);
					//tree->parent->fd[0][0] = dup(0); // stdin ok if on
					//tree->fd[1][1] = dup(1);
				}
				close(tree->parent->fd[0][0]);
				close(tree->parent->fd[0][1]);
				close(tree->fd[1][0]);
				close(tree->fd[1][1]);
			}
			execve(cmd, av, ev);
			tree->code_err = 127;
			free_tab(av);
			free_tab(ev); // char **
			//free_str(cmd); // char **
			exit(0);
		}
		if (builtin != NULL && tree->cmdr->path == NULL && tree->parent != NULL)
		{
			/* TO REMOVE AFTER FUNCTION ABOVE CREATED*/
			if (tree->fd[2][0] > 0)
			{
				dup2(tree->parent->fd[1][0], 0);
				dup2(tree->fd[2][1], 1);
				//tree->parent->fd[1][0] = dup(0);
				//tree->fd[2][1] = dup(1);
				close(tree->parent->fd[1][0]);
				close(tree->parent->fd[1][1]);
				close(tree->fd[2][0]);
				close(tree->fd[2][1]);
			}
			else
			{
				//dup2(tree->parent->fd[0][0], 0); // pb on strin if on
				//dup2(tree->fd[1][1], 1);
				//tree->parent->fd[0][0] = dup(0); // stdin ok if on
				tree->fd[1][1] = dup(1);
			}
			close(tree->parent->fd[0][0]);
			close(tree->parent->fd[0][1]);
			close(tree->fd[1][0]);
			close(tree->fd[1][1]);
			shell->return_err = builtin->f(av);
		}
		else if (builtin == NULL && cmd == NULL)
		{
			printf("%s : command not found", tree->cmdr->command);
			shell->return_err = 127;
		}
		else
			waitpid(tree->pid, &shell->return_err, WNOHANG);
		free_tab(av);
		free_tab(ev); // char**
		free_str(cmd);
		 // char *
		//return (free_tab(ev) + free_str(cmd) + free_tab(av));
	}
	return (0);
}
