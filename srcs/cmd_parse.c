/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/07/20 10:42:49 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ------------------------------------------------------- */
/*              STARTEND[0] = DEPART DU CHAR               */
/*	STARTEND[1] = POSITION DU CHAR TEST ET POSITION DE FIN */
/* ------------------------------------------------------- */
static char	*take_path(char *line, t_cmd *cmd)
{
	char	*ret;
	

	line = ft_skipspace(line);
	return (ret);
}

static char	*take_exec(char *line, t_cmd *cmd)
{

}

t_cmd	*cmd_parse(char *shell, t_cmd *cmd)
{
	char	*line;
	t_cmd	*new;

	line = shell;
	line = ft_skipspace(line);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!line || !new)
		ft_exit(MALLOCERR, 0, 0);
	new->path = take_path(&line, new);
	new->command = take_exec(&line, new);
	new->param = take_params(&line, new);
	new->option = take_option(&line, new);
	new->type = take_operator(&line, new);
	if (*line != '\0')
		cmd->next = cmd_parse(line, new);
	return (cmd);
}
