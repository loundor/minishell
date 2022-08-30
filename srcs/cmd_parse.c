/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/08/30 15:35:44 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ------------------| START OF PARSER |------------------- */
/*	The parser work in recurssive mode when the line is		*/
/*	empty after parssing. When the line containt something	*/
/*	we create a new structure cmd to place the new command.	*/
/*	See struct in minishell.h								*/
/* -------------------------------------------------------- */

t_cmd	*cmd_parse(char *shell, t_cmd *cmd)
{
	char	*line;
	t_cmd	*new;
	t_shell	*all;

	all = struct_passing(1, 0);
	all->tree = bt_create(shell);
	line = shell;
	(void)cmd;
	line = ft_skipspace(line);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		ft_exit(MALLOCERR, 1);
	line = take_path(line, new);
	line = take_exec(line, new);
	line = ft_skipspace(line);
	line = take_params(line, new);
//	line = take_operator(line, new);
	if (line && *line != '\0')
	{
		new->next = cmd_parse(line, new);
		new->next->prev = new;
	}
	else
		new->next = NULL;
	return (new);
}
