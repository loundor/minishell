/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:10:41 by stissera          #+#    #+#             */
/*   Updated: 2022/08/07 10:07:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ------------------| START OF PARSER |------------------- */
/*	Take the line after the first parsing, and cut the line	*/
/*	between the big priority (|| and &&). Take care about	*/
/*	the || and && in parenthesis, its must ignored! We work	*/
/*	that laterin binary tree.								*/
/*	EX:	(exec || exec2 && exec3) && /rep/exec -f "where..." */
/*	Should do 2 block:										*/
/*	First: (exec || exec2 && exec3) -> with priority &&		*/
/*	Second: /rep/exec -f "where..." -> whit priority end	*/
/* -------------------------------------------------------- */


/* int	big_split(char *shell)
{
	size_t	i;
	size_t	start;
	int		parenthesis;
	char	*line;

	i = 0;
	start = 0;
	parenthesis = 0;
	line = NULL;
	if (*line == '|' || *line == '&')
	{
		printf("syntax error near unexpected token %c", *line);
		return (1);
	}
	while ((line[i] != '\0' && line[i] != '||'
			&& line[i] != '&&') || (parenthesis > 0))
	{
		if (line[i] == '(')
			parenthesis++;
		if (line[i] == ')')
			parenthesis--;
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		exit(ft_exit(MALLOCERR, 1));
	while (start < i)
		line[start++] = *line++;
	line[start] = 0;
	if (*line != '\0')
		big_split(line);
	//// After work!
} */

/* ------------------| START OF PARSER |------------------- */
/*	The parser work in recurssive mode when the line is		*/
/*	empty after parssing. When the line containt something	*/
/*	we create a new structure cmd to place the new command.	*/
/*	See struct in minishell.h								*/
/* -------------------------------------------------------- */

t_cmd	*cmd_parse(char *shell, t_cmd *cmd)
{
//	big_split(char *shell);
	char	*line;
	t_cmd	*new;

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
	line = take_operator(line, new);
	if (line && *line != '\0')
	{
		new->next = cmd_parse(line, new);
		new->next->prev = new;
	}
	else
		new->next = NULL;
	return (new);
}
