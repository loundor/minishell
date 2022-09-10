/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_write_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:21:16 by stissera          #+#    #+#             */
/*   Updated: 2022/09/10 19:37:54 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tree_cmd(char *line, t_tree *tree)
{
	t_cmd	*new;
	new = NULL;
	if (bt_test_heredoc(line))
		line = tree_heredoc(line, tree);
 	else if (bt_test_input(line))
		line = tree_input_file(line, tree);
	else
	{
		if (bt_test_andor(line) || bt_test_pipe(line)
			|| bt_test_redir(line) || bt_test_appd(line))
			return (line);
		if (tree->type != 0)
			return (line);
		new = (t_cmd *)malloc(sizeof(t_cmd));
		if (!new)
			ft_exit(MALLOCERR, 1);
		line = ft_skipspace(line);
		line = take_path(line, new);
		line = ft_skipspace(line);
		line = take_exec(line, new);
		line = ft_skipspace(line);
		line = take_params(line, new);
		new->av = NULL;
		new->ev = NULL;
		new->built = NULL;
		tree->cmdr = new;
		line = NULL;
	}
	return (line);
}
