/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:17:36 by stissera          #+#    #+#             */
/*   Updated: 2022/09/14 10:44:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_node_type(char *line, t_tree *tree, int t, size_t i)
{
	char	*work;
	size_t	s;

	s = 0;
	work = (char *)malloc(sizeof(char) * (i));
	if (!work)
		exit(ft_exit(MALLOCERR, 1));
	while (s < i - 1)
		work[s++] = *line++;
	work[s] = '\0';
	if (line++ && (t == 1 || t == 4 || t == 6))
		line +=2;
	else if (t == 2 || t == 3 || t == 5 || t == 7)
		line += 3;
	tree->type = t;
	tree->left = bt_create(work);
	tree->left->parent = tree;
	free(work);
	return (line);
}

char	*tree_andor(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_andor(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, get_cmd_type(&line[i[0]]), i[0]);
	return (line);
}

static char	*parenthesis_node(char *line, size_t i, t_tree *tree)
{
	char	*work;
	char	*workr;
	size_t	s;

	s = 0;
	workr = NULL;
	work = (char *)malloc(sizeof(char) * (i - 2));
	if (!work)
		exit(ft_exit(MALLOCERR, 1));
	while (s < (i - 3))
		work[s++] = *line++;
	work[s] = '\0';
	line ++;	
	line = ft_skipspace(line);
	if (line && line != 0)
	{
		tree->type = get_cmd_type(line);
		line += 2;
		tree->left = bt_create(work);
		tree->left->parent = tree;
	}
	else
	{
		workr = bt_create_if(work, tree);
		if (workr != NULL)
		{
			tree->right = bt_create(workr);
			tree->right->parent = tree;
		}
	}
	free(work);
	return (line);
}

char	*tree_parenthesis(char *line, t_tree *tree)
{
	size_t	i[3];

	if (line && *line == '(')
	{
		i[0] = 0;
		i[1] = 0;
		while (line[i[0]] == '(' || i[1])
		{
			while (line[i[0]] != ')')
			{
				if (line[i[0]] == '(')
					i[1]++;
				i[0]++;
			}
			i[1]--;
			i[0]++;
		}
		if (i[0] <= 1)
			return (&line[2]);
		line = parenthesis_node(&line[2], i[0], tree);
	}
	return (line);
}
