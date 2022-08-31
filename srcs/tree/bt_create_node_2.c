/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_node_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:19:26 by stissera          #+#    #+#             */
/*   Updated: 2022/08/31 22:30:14 by stissera         ###   ########.fr       */
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

	i[0] = bt_test_redir(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, 4, i[0]);
	return (line);
}

char	*tree_append(char *line, t_tree *tree)
{
	size_t	i[2];

	i[0] = bt_test_appd(line);
	i[1] = 0;
	if (i[0] > 0)
		line = add_node_type(line, tree, 5, i[0]);
	return (line);
}
