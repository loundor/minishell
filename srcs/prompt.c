/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 21:33:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -----------------| WRITE WHAT YOU WANT! |--------------- */
/*	After initialisation, write create the prompt.			*/
/*	The prompt wait until the command is validate, check	*/
/* the command is not null and put the command line in core	*/
/* -------------------------------------------------------- */

static	char *get_title_shell(void)
{
	char	*path;
	char	*home;
	char	*title;
	int		i;
	
	i = 0;
	home = take_dollar("$HOME");
	path = getcwd((void *)0, 0);
	if (home != NULL && !ft_strncmp(home, path, ft_strlen(home) - 1))
	{
		while (path[i] && home[i] == path[i])
			i++;
		if (home[i] == 0 && (path[i] == 0 || path[i] == '/'))
			title = ft_strjoin("\e[1;32mminishell-0.1\e[0m:\e[1;34m~", &path[i]);
		else
			title = ft_strjoin("\e[1;32mminishell-0.1\e[0m:\e[1;34m", path);
	}
	else
		title = ft_strjoin("\e[1;32mminishell-0.1\e[0m:\e[1;34m", path);
	free(path);
	path = ft_strjoin(title, "\e[0m$ ");
	free(title);
	if (home != NULL)
		free(home);
	return (path);
}

int	prompt(t_shell *shell)
{
	char	*path;
	char	*line;

	while (!shell->line || strcmp(shell->line, "exit"))
	{
		shell->cmd = NULL;
		if (shell->line != NULL)
			free(shell->line);
		path = get_title_shell();
		shell->line = readline(path);
		line = shell->line;
		line = ft_skipspace(line);
		free(path);
		if (line)
		{
			add_history(shell->line);
			if (core(shell))
				printf("An error was occured!\n");
		}
		else
			continue ;
		ft_exit(0, 3);
		line = NULL;
	}
	return (0);
}

/* ----------------------| THE CORE! |--------------------- */
/*	After the command line validation, we start to check	*/
/*	what the user want. We parse the line into comd struct	*/
/*	and go to a loop to do the right direction of all cmd	*/
/*	After some command, we put the command in a history		*/
/* -------------------------------------------------------- */
int	core(t_shell *shell)
{
	t_builtins	*builtin;
	char		*line;

	//line = line_parse(shell->line);
	line = parse_space(shell->line);
	if (line == NULL)
		return (0);
	free(shell->line);
	shell->line = line;
	shell->cmd = cmd_parse(shell->line, shell->cmd);
	builtin = search_builtin(shell->cmd->command, shell->builtin);
 printf("--> \e[32mPATH: %s\e[0m\n--> \e[33mCMD: %s\e[0m\n--> \e[34mPARAM: %s\e[0m\n", shell->cmd->path, shell->cmd->command, shell->cmd->param);
	prepare_exe(shell);
	if (builtin != NULL && shell->cmd->path == NULL)
		builtin->f(shell);
	return (0);
}

int	prepare_exe(t_shell *shell)
{
	(void)shell;
	return (0);
}
