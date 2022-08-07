/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_test_sep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:15:55 by stissera          #+#    #+#             */
/*   Updated: 2022/08/07 22:38:31 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* see for add a type int in prototype but take care && || << */
/* (that can do only in one or two functions) */

int	bt_test_and(char *line)
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
		}
		if (line[i] == '&' && line[i + 1] == '&')
			return (i);
		i++;
	}
	return (0);
}

int	bt_test_or(char *line)
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
		}
		if (line[i] == '|' && line[i + 1] == '|')
			return (i);
		i++;
	}
	return (0);
}

int	bt_test_pipe(char *line)
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
		}
		if (line[i] == '|' && line[i + 1] != '|')
			return (i);
		i++;
	}
	return (0);
}

int	bt_test_redir(char *line)
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
				line++;
			}
			parenthesis--;
		}
		if (line[i] == '>' && line[i + 1] != '>')
			return (i);
		i++;
	}
	return (0);
}

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
		}
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
		}
		if (line[i] == '<' && line[i + 1] != '<')
			return (i);
		i++;
	}
	return (i);
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
		}
		if (line[i] == '<' && line[i + 1] == '<')
			return (i);
		i++;
	}
	return (i);
}
