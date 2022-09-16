/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:44:22 by stissera          #+#    #+#             */
/*   Updated: 2022/09/16 23:31:48 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static char	*do_line(char *line)
{
	char 	*ret;

	if (*line == '\'')
		ret = take_single_quote(line);
	else
		ret = take_double_quote(line);
	return (ret);
}

int	var_to_exec(t_cmd *cmd)
{
	if (cmd->param && cmd->param[0] != NULL)
		cmd->command = do_line(cmd->command) + free_str(cmd->command);
	if (cmd->param && cmd->param[0] != NULL)
		cmd->param = do_line(cmd->param) + free_str(cmd->param);
	return (0);
}