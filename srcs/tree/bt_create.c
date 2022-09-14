/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:57:32 by stissera          #+#    #+#             */
/*   Updated: 2022/09/14 09:29:08 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -------------------| MAKE A TREE B |-------------------- */
/*	After parsing the cmd, we get this and create a tree.	*/
/*	We always check if a separator exist, and take the cmd	*/
/*	before the separator and call the function separator	*/
/*	There functions are a recursive, there function make a	*/
/*	root about type of separator and a left branch recall	*/
/*	the function tree, after it make a right branch if there*/
/*	are always something of the part of cmd and call tree	*/
/*	The function bt_create is the principal function, it	*/
/*	always make a root, the another function do the banch if*/
/*	need.													*/
/* -------------------------------------------------------- */
/*		WE CAN MAYBE REDUCE THE NUMBER OF FUCNTION			*/
/* -------------------------------------------------------- */

char	*bt_create_if(char *line, t_tree *tree)
{
	if (*line == '(')
		line = tree_parenthesis(line, tree);
	else if (bt_test_andor(line))
		line = tree_andor(line, tree);
	else if (bt_test_pipe(line))
		line = tree_pipe(line, tree);
	else if (bt_test_appd(line))
		line = tree_append(line, tree);
	else if (bt_test_redir(line))
		line = tree_redirection(line, tree);
	else
	{
		line = tree_cmd(line, tree);
	}
	return (line);
}

t_tree	*bt_create(char *line)
{
	t_tree	*tree;

	tree = NULL;
	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		exit(ft_exit(MALLOCERR, 1));
	tree->type = 0;
	tree->left = NULL;
	tree->right = NULL;
	tree->cmdr = NULL;
	tree->parent = NULL;
	line = bt_create_if(line, tree);
	line = ft_skipspace(line);
	if (line && *line != '\0')
	{
		tree->right = bt_create(line);
		tree->right->parent = tree;
	}
	if (tree->type != 0)
		return (tree);
	return (tree);
}

void	free_bt(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		free_bt((t_tree *)tree->left);
	if (tree->right && tree->right != NULL)
		free_bt((t_tree *)tree->right);
	if (tree->cmdr && tree->cmdr != NULL)
		free_cmd((t_cmd *)tree->cmdr);
	free(tree);
}
