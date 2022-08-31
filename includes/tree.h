/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:23:58 by stissera          #+#    #+#             */
/*   Updated: 2022/08/31 22:44:32 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

t_tree	*bt_create(char *line);

int		skip_part_char(char *line, size_t *i, char type);
int		bt_test_appd(char *line);
int		bt_test_input(char *line);
int		bt_test_heredoc(char *line);
int		bt_test_and(char *line);
int		bt_test_or(char *line);
int		bt_test_pipe(char *line);
int		bt_test_redir(char *line);

char	*add_node_type(char *line, t_tree *tree, int t, size_t i);
char	*tree_and(char *line, t_tree *tree);
char	*tree_or(char *line, t_tree *tree);
char	*tree_parenthesis(char *line, t_tree *tree);
char	*tree_pipe(char *line, t_tree *tree);
char	*tree_redirection(char *line, t_tree *tree);
char	*tree_append(char *line, t_tree *tree);

char	*tree_cmd(char *line, t_tree *tree);

void	free_bt(t_tree *tree);

#endif