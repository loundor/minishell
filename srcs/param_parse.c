/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:35:56 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 12:22:36 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -------------------| SEARCH $VAR |---------------------- */
/*	Search and return de value of asked variable			*/
/*	Check and compare the asked variable in env struct		*/
/*	When env->next is flase that s mark en of struct		*/
/*	Check if var as same of env->var, if same use ft_strdup */
/*	and return the right variable, otherwise return NULL	*/
/* -------------------------------------------------------- */
static char	*search_var(char *var)
{
	t_env	*env;
	t_env	*tmp;
	int		round;
	char	*line;

	env = (t_env *)struct_passing(2, NULL);
	tmp = env;
	round = 0;
	while (ft_strcmp(var, tmp->env_var[0]) && tmp->next_env != NULL)
	{
		tmp = tmp->next_env;
		round = 1;
	}
	if (!ft_strcmp(var, tmp->env_var[0]))
		line = ft_strdup(tmp->env_var[1]);
	else
		return (NULL);
	return (line);
}

/* ------------------|	SINGLE QUOTE |--------------------- */
/*	Take the line until a single quote and return that in a */
/*	malloced variable. If end of line without single quote	*/
/*	open a HEREDOC to finish the right line.				*/
/*	HEREDOC NO ALLREADY IMPLEMENTED!!!!!					*/
/* -------------------------------------------------------- */
static char	*take_single_quote(char *param)
{
	char	*line;
	size_t	start;
	size_t	stop;
	int		space;

	start = -1;
	space = 1;
	stop = 0;
	line = ++param;
	while (line[stop] != '\'')
		stop++;
	if (line[stop + 1] == ' ')
		space = 2;
	line = (char *)malloc(sizeof(char) * stop + 2);
	if (!line)
		exit(ft_exit(MALLOCERR, 2));
	while (++start < stop)
		line[start] = *param++;
	if (space == 2)
		line[start++] = 32;
	line[start] = '\0';
	return (line);
}

/* ---------------|					 |------------------- */
/*															*/
/* -------------------------------------------------------- */
static char	*take_double_quote(char *param)
{
	write (1, "DOUBLE QUOTES\n", 15);
	(void) param;
	return (NULL);
}

/* --------------| WITH $VAR TO ENV VAR |------------------ */
/*	Take the variable (until space, no alphanum caractere	*/
/*	or _) and call the function search_var to get the var	*/
/*	if var don't exist, we get en NULL return				*/
/*	TAKE CARE ABOUT THE SPACE AFTER THE $VAR!!!! need impl.	*/
/* -------------------------------------------------------- */
char	*take_dollar(char *param)
{
	char	*line;
	char	*search;
	size_t	start;
	size_t	end;

	start = -1;
	end = 0;
	param++;
	while (param[end] != 0 && (ft_isalnum(param[end]) || param[end] == '_'))
		end++;
	search = (char *)malloc(sizeof(char) * (end + 1));
	if (!search)
		exit(ft_exit(MALLOCERR, 1));
	while (++start < end)
		search[start] = *(param++);
	search[start] = 0;
	line = search_var(search);
	if (line != NULL)
		free(search);
	return (line);
}

/* ---------------| PARAMETER PARSSING |------------------- */
/*	Get the pointer of cmd->param. Of every caractere check	*/
/*	if it's a signle or double quote and launch the funct	*/
/*	if need. Recept the new created line, and free the last	*/
/*	linenbak 0 -> parssing str								*/
/*	linenbak 1 -> str to parsse								*/
/*				/!\ REWRITE THE EXPLAIN BLOCK!!!			*/
/* -------------------------------------------------------- */

char	*param_parse(char *cmd)
{
	char	*line;
	char	*ret[2];
	char	*tmp;
	size_t	start;
	size_t	end;

	tmp = NULL;
	ret[0] = NULL;
	start = -1;
	line = cmd;
	end = 0;
	while (line[end] != 0 && line[end] != 39 && line[end] != 34
		&& !(line[end] == 36 && line[end + 1] != 32))
		end++;
	if (end == ft_strlen(line))
		return (cmd);
	if (end != 0)
	{
		ret[0] = (char *)malloc(sizeof(char) * (end + 1));
		if (!ret[0])
			exit(ft_exit(MALLOCERR, 2));
		while (++start < end)
			ret[0][start] = *line++;
		ret[0][start] = '\0';
	}
	if (*line == '\'')
	{
		tmp = take_single_quote(line);
		if (ret[0] != NULL)
		{
			ret[1] = ft_strjoin(ret[0], tmp);
			free(tmp);
		}
		else
			ret[1] = tmp;
		while (*(++line) != '\'');
		line++;
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
	}
	else if (*line == '\"')
	{
		tmp = take_double_quote(line);
		ret[1] = ft_strjoin(ret[0], tmp);
		start = -1;
		while (++start <= ft_strlen(tmp))
			line++;
		free(tmp);
		free (ret[0]);
		ret[0] = ret[1];
	}
	else if (*line == '$')
	{
		tmp = take_dollar(line);
		if (ret[0] != NULL && tmp != NULL)
		{
			ret[1] = ft_strjoin(ret[0], tmp);
			free(tmp);
		}
		else if (ret[0] != NULL && tmp == NULL)
			ret[1] = ft_strdup(ret[0]);
		else if (ret[0] == NULL && tmp != NULL)
			ret[1] = tmp;
		else
			ret[1] = 0;
		while (*(++line) != '\0' && (ft_isalnum(*line) || *line == '_'));
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
		ft_putstr_fd(line, 1);
	}
	if (line != NULL && *line != 0)
	{
		line = ft_skipspace(line);
		tmp = param_parse(line);
		if (ret[0] != NULL)
			ret[1] = ft_strjoin(ret[0], tmp);
		else
			ret[1] = ft_strdup(tmp);
		if (ret[0] != NULL)
			free (ret[0]);
		ret[0] = ret[1];
	}
	return (ret[0]);
}
