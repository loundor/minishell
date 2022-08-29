/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:09:24 by stissera          #+#    #+#             */
/*   Updated: 2022/08/29 10:38:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_shell *shell)
{
	char	*line;
	char	*bakline;
	int		new_line;

	line = line_parse(shell->cmd->param);
	bakline = line;
	line = ft_skipspace(line);
	new_line = 0;
	if (line != NULL)
	{
		if (!ft_strncmp(line, "-n ", 3) || !ft_strncmp(line, "-n\0", 3))
		{
			new_line = 1;
			while (*line != ' ' && *line != 0)
				line++;
			line = ft_skipspace(line);
		}
		while (line != 0 && *line)
			write(1, line++, 1);
		free (bakline);
		if (new_line == 1)
			return (0);
	}
	write(1, "\n", 1);
	return (0);
}
