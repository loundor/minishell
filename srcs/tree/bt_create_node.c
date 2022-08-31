/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:17:36 by stissera          #+#    #+#             */
/*   Updated: 2022/08/31 22:53:47 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_node_type(char *line, t_tree *tree, int t, size_t i)
{
	char	*work;
	size_t	s;

	s = 0;
	work = (char *)malloc(sizeof(char) * (i + 1));
	if (!work)
		exit(ft_exit(MALLOCERR, 1));
	while (s < i)
		work[s++] = *line++;
	work[s] = '\0';
	if (t == 1 || t == 4)
		line++;
	else if (t == 2 || t == 3 || t == 5)
		line += 2;
	tree->type = t;
	tree->left = bt_create(work);
	tree->left->parent = tree;
	free(work);
	return (line);
}

char	*tree_and(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_and(line);
	i[1] = 0;
	if (i[0] > 0)
        line = add_node_type(line, tree, 3, i[0]);
	return (line);
}

char	*tree_or(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_or(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, 2, i[0]);
	return (line);
}

static char	*parenthesis_node(char *line, size_t i, t_tree *tree)
{
	char	*work;
	size_t	s;

	s = 0;
	work = (char *)malloc(sizeof(char) * (i - 1));
	if (!work)
		exit(ft_exit(MALLOCERR, 1));
	while (s < (i - 2))
		work[s++] = *line++;
	work[s] = '\0';
	line ++;
	line = ft_skipspace(line);
	tree->type = get_cmd_type(line);
	line += 2;
	tree->left = bt_create(work);
	tree->left->parent = tree;
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
		i[2] = 0;
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
		line++;
		if (i[0] <= 1)
			return (++line);
		line = parenthesis_node(line, i[0], tree);
	}
	return (line);
}