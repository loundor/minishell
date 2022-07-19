/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/07/19 18:00:18 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ------------------------------------------------------- */
/*              STARTEND[0] = DEPART DU CHAR               */
/*	STARTEND[1] = POSITION DU CHAR TEST ET POSITION DE FIN */
/* ------------------------------------------------------- */
t_cmd	cmd_parse(char *shell)
{
	size_t	startend[2];
	char	*cmd;
	t_cmd	*ret;

	startend[0] = 0;
	startend[1] = -1;
	cmd = shell;
	while (cmd[++startend[1]] != '\0')
	{
		ret = (t_cmd *)malloc(sizeof(t_cmd));
		if (!ret)
			ft_exit(MALLOCERR, 0, 0);
		if (cmd[startend[1]] == '|')
		{
			if (cmd[startend[1] + 1] == '|')
				cmd_or(shell, startend); //AJOUTER +1 AU STARTEND[1]
			else
				cmd_pipe(shell, startend);
		}
		else if (cmd[startend[1]] == '&' && cmd[startend[1] + 1] == '&')
			cmd_and(shell, startend);
		else if (cmd[startend[1]] == '>')
		{
			if (cmd[startend[1] + 1] == '>')
				cmd_append(shell, startend); //AJOUTER +1 AU STARTEND[1]
			else
				cmd_fd(shell, startend);
		}
		else if (cmd[startend[1]] == '<')
		{
			if (cmd[startend[1] + 1] == '<')
				cmd_append(shell, startend); //AJOUTER +1 AU STARTEND[1]
			else
				cmd_fd(shell, startend);
		}
		while (ft_isspace(cmd[startend[1]]))
			startend[1]++;
	}
	return (NULL);
}
