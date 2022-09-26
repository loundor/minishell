/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/09/26 18:16:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -----------------| WRITE WHAT YOU WANT! |--------------- */
/*	After initialisation, write create the prompt.			*/
/*	The prompt wait until the command is validate, check	*/
/* the command is not null and put the command line in core	*/
/* -------------------------------------------------------- */

static char	*get_title_shell(void)
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
			title = ft_strjoin(
				"\001\e[1;32\002mminishell-0.2\001\e[0m\002:\001\e[1;34m\002~"
				, &path[i]);
		else
			title = ft_strjoin(
				"\001\e[1;32\002mminishell-0.2\001\e[0m\002:\001\e[1;34m\002"
				, path);
	}
	else
		title = ft_strjoin(
			"\001\e[1;32\002mminishell-0.2\001\e[0m\002:\001\e[1;34m\002"
			, path);
	free(path);
	path = ft_strjoin(title, "\001\e[0m$\002 ");
	free(title);
	if (home != NULL)
		free(home);
	return (path);
}

int	prompt(t_shell *shell)
{
	char	*path;
	char	*line;

	while (!shell->line || (ft_strncmp(shell->line, "exit", 4)))
	{
		setsig(0);
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
		else if (shell->line == NULL)
			return (write(1, "\n", 1) * 0);
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
	char		*line;

	line = parse_space(ft_skipspace(shell->line));
	line = test_line(line);
	if (line == NULL)
	{
		shell->return_err = 1;
		return (0);
	}
	free(shell->line);
	shell->line = line;
	shell->tree = bt_create(shell->line);
	put_last_tree(shell->tree);
	pre_prepare_exec(shell, shell->tree);
	wait_process(shell->tree, shell);
	close_all_fd(shell->tree);
	free(shell->line);
	free_bt(shell->tree);
	shell->tree = NULL;
	return (0);
}