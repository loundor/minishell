/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:57:32 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 13:25:35 by stissera         ###   ########.fr       */
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

static char	*tree_and(char *line, t_tree *tree)
{
	char	*work;
	size_t	i[2];

	work = NULL;
	i[0] = bt_test_and(line);
	i[1] = 0;
	if (i[0] > 0)
	{
		work = (char *)malloc(sizeof(char) * (i[0] + 1));
		if (!work)
			exit(ft_exit(MALLOCERR, 1));
		while (i[1] < i[0])
			work[i[1]++] = *line++;
		work[i[1]] = '\0';
		line += 2;
		tree->type = 3;
		tree->left = bt_create(work);
		tree->left->parent = tree;
		free(work);
	}
	return (line);
}

static char	*tree_or(char *line, t_tree *tree)
{
	char	*work;
	size_t	i[2];

	work = NULL;
	i[0] = bt_test_or(line);
	i[1] = 0;
	if (i[0] > 0)
	{
		work = (char *)malloc(sizeof(char) * (i[0] + 1));
		if (!work)
			exit(ft_exit(MALLOCERR, 1));
		while (i[1] < i[0])
			work[i[1]++] = *line++;
		work[i[1]] = '\0';
		line += 2;
		tree->type = 2;
		tree->left = bt_create(work);
		tree->left->parent = tree;
		free(work);
	}
	return (line);
}

// CERTAINEMENT A METTRE DANS UN TEST
static char	*tree_parenthesis(char *line, t_tree *tree)
{
	char	*work;
	size_t	i[3];

	if (line && *line == '(')
	{
		i[0] = 0;
		i[1] = 0;
		i[2] = 0;
		while (line[i[0]] == '(' || i[2])
		{
			while (line[i[0]] != ')')
			{
				if (line[i[0]] == '(')
					i[2]++;
				i[0]++;
			}
			i[2]--;
			i[0]++;
		}
		line++;
		if (i[0] <= 1)
		{
			line++;
			return (line);
		}
		work = (char *)malloc(sizeof(char) * (i[0] - 1));
		if (!work)
			exit(ft_exit(MALLOCERR, 1));
		while (i[1] < (i[0] - 2))
			work[i[1]++] = *line++;
		work[i[1]] = '\0';
		line ++;
		line = ft_skipspace(line);
		tree->type = get_cmd_type(line);
		line += 2;
		tree->left = bt_create(work);
		tree->left->parent = tree;
		free(work); // Check if need this free
	}
	return (line);
}

static char	*tree_pipe(char *line, t_tree *tree)
{
	char	*work;
	size_t	i[2];

	work = NULL;
	i[0] = bt_test_pipe(line);
	i[1] = 0;
	if (i[0] > 0)
	{
		work = (char *)malloc(sizeof(char) * (i[0] + 1));
		if (!work)
			exit(ft_exit(MALLOCERR, 1));
		while (i[1] < i[0])
			work[i[1]++] = *line++;
		work[i[1]] = '\0';
		line++;
		tree->type = 1;
		tree->left = bt_create(work);
		tree->left->parent = tree;
		free(work);
	}
	return (line);
}

static char	*tree_redirection(char *line, t_tree *tree)
{
	char	*work;
	size_t	i[2];

	work = NULL;
	i[0] = bt_test_redir(line);
	i[1] = 0;
	if (i[0] > 0)
	{
		work = (char *)malloc(sizeof(char) * (i[0] + 1));
		if (!work)
			exit(ft_exit(MALLOCERR, 1));
		while (i[1] < i[0])
			work[i[1]++] = *line++;
		work[i[1]] = '\0';
		line++;
		tree->type = 4;
		tree->left = bt_create(work);
		tree->left->parent = tree;
		free(work);
	}
	return (line);
}

static char	*tree_append(char *line, t_tree *tree)
{
	char	*work;
	size_t	i[2];

	work = NULL;
	i[0] = bt_test_appd(line);
	i[1] = 0;
	if (i[0] > 0)
	{
		work = (char *)malloc(sizeof(char) * (i[0] + 1));
		if (!work)
			exit(ft_exit(MALLOCERR, 1));
		while (i[1] < i[0])
			work[i[1]++] = *line++;
		work[i[1]] = '\0';
		line++;
		tree->type = 5;
		tree->left = bt_create(work);
		tree->left->parent = tree;
		free(work);
	}
	return (line);
}

static char	*tree_cmd(char *line, t_tree *tree)
{
	if (bt_test_and(line) || bt_test_or(line) || bt_test_pipe(line)
		|| bt_test_redir(line) || bt_test_appd(line))
		return (line);
	if (tree->type != 0)
		return (line);
	tree->cmd = ft_strdup(line);
	line = NULL;
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
	if (*line == '(')
		line = tree_parenthesis(line, tree);
	else if (bt_test_and(line))
		line = tree_and(line, tree);
	else if (bt_test_or(line))
		line = tree_or(line, tree);
	else if (bt_test_pipe(line))
		line = tree_pipe(line, tree);
	else if (bt_test_redir(line))
		line = tree_redirection(line, tree);
	else if (bt_test_appd(line))
		line = tree_append(line, tree);
	else
	{
		//	else if (bt_test_and(line))
		//		line = tree_heredoc(line, tree);
		line = tree_cmd(line, tree);
	}
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
