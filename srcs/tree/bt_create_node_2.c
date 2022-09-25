/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_node_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:19:26 by stissera          #+#    #+#             */
/*   Updated: 2022/09/25 21:00:13 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tree_pipe(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_pipe(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, 1, i[0]);
	return (line);
}

char	*tree_redirection(char *line, t_tree *tree)
{
	size_t	i[2];
	int		type;

	if (bt_test_redir(line) && (bt_test_redir(line) < bt_test_appd(line) || bt_test_appd(line) == 0 ))
	{
		i[0] = bt_test_redir(line);
		type = 4;
	}
	else
	{
		i[0] = bt_test_appd(line);
		type = 5;
	}
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, type, i[0]);
	return (++line);
}

char	*tree_input_file(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_input(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, 6, i[0]);
	return (++line);
}

char	*tree_heredoc(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_heredoc(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, 7, i[0]);
	return (++line);
}