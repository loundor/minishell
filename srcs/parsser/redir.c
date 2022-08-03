/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:33:52 by stissera          #+#    #+#             */
/*   Updated: 2022/08/03 17:18:21 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* --------------| PARSSE BETWEEN COMMAND |---------------- */
/*	We check the rest of the line. If the line egal \0 that	*/
/*	means the command is finish otherise we put the			*/
/*	variable to TYPE in struct to know what the redirection */
/*	pipe, or binary operation is.							*/
/* -------------------------------------------------------- */
char	*take_operator(char *line, t_cmd *cmd)
{
	if (!line || *line == '\0')
	{
		cmd->type = 0;
		return (NULL);
	}
	if (!ft_strncmp(line, "||", 2))
		cmd->type = 2;
	else if (!ft_strncmp(line, "|", 1))
		cmd->type = 1;
	if (!ft_strncmp(line, "&&", 2))
		cmd->type = 3;
	if (!ft_strncmp(line, "<<", 2))
		cmd->type = 7;
	else if (!ft_strncmp(line, "<", 1))
		cmd->type = 6;
	if (!ft_strncmp(line, ">>", 2))
		cmd->type = 5;
	else if (!ft_strncmp(line, ">", 1))
		cmd->type = 4;
	if (cmd->type == 5 || cmd->type == 7 || cmd->type == 2 || cmd->type == 3)
		line += 2;
	else
		line++;
	line = ft_skipspace(line);
	return (line);
}
