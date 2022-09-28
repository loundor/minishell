/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:50:58 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 21:12:49 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_parenthesis(char *line)
{
	int	parenthesis;

	parenthesis = 0;
	while (line && *line != 0)
	{
		if (*line == '(')
		{
			if (line[1] == 0 || get_cmd_type(&line[2]) || line[2] == ')')
				return (8);
			parenthesis++;
		}
		if (*line == ')')
		{
			if (get_cmd_type(&line[-2]))
				return (get_cmd_type(&line[-2]));
			parenthesis--;
		}
		line++;
	}
	if (parenthesis == 0)
		return (0);
	return (8);
}

static int	line_error(int type, char *line)
{
	char	*caractere;

	caractere = 0;
	if (type == 8)
		printf("missing parenthesis\n");
	else if (type == 7)
		caractere = "<<";
	else if (type == 6)
		caractere = "<";
	else if (type == 5)
		caractere = ">>";
	else if (type == 4)
		caractere = ">";
	else if (type == 3)
		caractere = "&&";
	else if (type == 2)
		caractere = "||";
	else
		caractere = "|";
	if (caractere != 0)
		printf("parse error near '%s'\n", caractere);
	return (0 + free_str(line));
}

static int	check_separator(char *line)
{
	while (line && *line != 0)
	{
		while (*line != 0 && !get_cmd_type(line))
			line++;
		if (*line != 0 && (get_cmd_type(line) == 2 || get_cmd_type(line) == 3
				|| get_cmd_type(line) == 5 || get_cmd_type(line) == 7))
		{
			if (line[2] == 0 || get_cmd_type(&line[2])
				|| get_cmd_type(&line[3]) || line[2] == '&' || line[3] == '&')
				return (get_cmd_type(line));
			line += 3;
		}
		else if (*line != 0 && (get_cmd_type(line) == 1
				|| get_cmd_type(line) == 4 || get_cmd_type(line) == 6))
		{
			if (line[1] == 0 || get_cmd_type(&line[1])
				|| get_cmd_type(&line[2]) || line[1] == '&' || line[2] == '&')
				return (get_cmd_type(line));
			line += 2;
		}
	}
	return (0);
}

char	*test_line(char *line)
{
	if (*line == ')' || line[2] == ')')
		return (NULL + line_error(8, line));
	if (get_cmd_type(line))
		return (NULL + line_error(get_cmd_type(line), line));
	if (check_parenthesis(line))
		return (NULL + line_error(check_parenthesis(line), line));
	if (check_separator(line))
		return (NULL + line_error(check_separator(line), line));
	return (line);
}
