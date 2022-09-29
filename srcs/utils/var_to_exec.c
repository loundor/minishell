/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:44:22 by stissera          #+#    #+#             */
/*   Updated: 2022/09/29 11:14:36 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*do_var(char *line)
{
	char	*ret;
	char	*dollar;
	int		quotes;

	dollar = NULL;
	ret = NULL;
	quotes = 1;
	while (*line)
	{
		if (*line != 0 && *line == '"')
			quotes *= -1;
		if (*line != 0 && *line == '\'' && quotes == 1)
		{
			ret = ft_joincts(ret, *line++) + free_str(ret);
			while (*line != 0 && *line != '\'')
				ret = ft_joincts(ret, *line++) + free_str(ret);
		}
		if (*line != 0 && *line == '$' && (line [1] != 0 && line [1] != ' '
				&& line[1] != '\'' && line[1] != '"' && line[1] != '$'))
		{
			dollar = take_dollar(line++);
			if (ret != NULL)
				ret = ft_strjoin(ret, dollar) + free_str(dollar);
			else
				ret = ft_strdup(dollar) + free_str(dollar);
			while (*line != 0 && (ft_isalnum(*line) || *line == '_'
					|| *line == '?'))
				line++;
			continue ;
		}
		ret = ft_joincts(ret, *line++) + free_str(ret);
	}
	return (ret);
}

static char	*ft_write_cmd(char *line, size_t i, size_t count)
{
	char	quote;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (i - count + 1));
	if (!ret)
		exit (ft_exit(errno, 1));
	i = 0;
	while (*line != 0)
	{
		if (*line != 0 && (*line == '\'' || *line == '"'))
		{
			quote = *line++;
			while (*line != 0 && *line != quote)
				ret[i++] = *line++;
			line++;
			continue ;
		}
		ret[i++] = *line++;
	}
	ret[i] = 0;
	return (ret);
}

static char	*finish_cmd(char *line)
{
	char	*ret;
	char	quote;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i] != 0)
	{
		if (line[i] != 0 && (line[i] == '\'' || line[i] == '"'))
		{
			quote = line[i++];
			while (line[i] != 0 && line[i] != quote)
				i++;
			i++;
			count += 2;
			continue ;
		}
		i++;
	}
	ret = ft_write_cmd(line, i, count);
	return (ret);
}

int	var_to_exec(t_cmd *cmd)
{
	if (cmd->command && cmd->command[0] != 0)
	{
		cmd->command = do_var(cmd->command) + free_str(cmd->command);
		cmd->command = finish_cmd(cmd->command) + free_str(cmd->command);
	}
	if (cmd->param && cmd->param[0] != 0)
		cmd->param = do_var(cmd->param) + free_str(cmd->param);
	return (0);
}
