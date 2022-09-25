/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_test_sep_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:22:40 by stissera          #+#    #+#             */
/*   Updated: 2022/09/25 20:50:12 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bt_test_appd(char *line)
{
	int		parenthesis;
	size_t	i;

	i = 0;
	parenthesis = 0;
	while (line[i] || line[i] != '\0')
	{
		while (line[i] == '(' || parenthesis != 0)
		{
			while (line[i] != ')')
			{
				if (line[i] == '(')
					parenthesis++;
				i++;
			}
			parenthesis--;
			i++;
		}
		if (skip_part_char(line, &i, '\'') || skip_part_char(line, &i, '"'))
			continue ;
		if (line[i] == '>' && line[i + 1] == '>')
			return (i);
		i++;
	}
	return (0);
}

int	bt_test_input(char *line)
{
	int		parenthesis;
	size_t	i;

	i = 0;
	parenthesis = 0;
	while (line[i] || line[i] != '\0')
	{
		while (line[i] == '(' || parenthesis != 0)
		{
			while (line[i] != ')')
			{
				if (line[i] == '(')
					parenthesis++;
				i++;
			}
			parenthesis--;
			i++;
		}
		if (skip_part_char(line, &i, '\'') || skip_part_char(line, &i, '"'))
			continue ;
		if (line[i] == '<' && line[i + 1] != '<')
			return (i);
		i++;
	}
	return (0);
}

int	bt_test_heredoc(char *line)
{
	int		parenthesis;
	size_t	i;

	i = 0;
	parenthesis = 0;
	while (line[i] || line[i] != '\0')
	{
		while (line[i] == '(' || parenthesis != 0)
		{
			while (line[i] != ')')
			{
				if (line[i] == '(')
					parenthesis++;
				i++;
			}
			parenthesis--;
			i++;
		}
		if (skip_part_char(line, &i, '\'') || skip_part_char(line, &i, '"'))
			continue ;
		if (line[i] == '<' && line[i + 1] == '<')
			return (i);
		i++;
	}
	return (0);
}
