/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/09/15 10:00:25 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -----------------| WRITE WHAT YOU WANT! |--------------- */
/*	After initialisation, write create the prompt.			*/
/*	The prompt wait until the command is validate, check	*/
/* the command is not null and put the command line in core	*/
/* -------------------------------------------------------- */

static char	*test_line(char *line)
{
	int		good;
	int		parenthesis;
	char	*bak;

	good = 0;
	parenthesis = 0;
	bak = line;
	while (line && *line != 0)
	{
		if (*line == '\'' || *line == '"')
		{
			if (*line != 0 && *line == '\'')
				while (*line != 0 && *++line != '\'')
					;
			if (*line != 0 && *line == '"')
				while (*line != 0 && *++line != '"')
					;
			continue ;
		}
		// test if ex " qwe |     | qweqw" exist... it a error too.
		if (get_cmd_type(line) == 2 || get_cmd_type(line) == 3
			|| get_cmd_type(line) == 5 || get_cmd_type(line) == 7)
		{
			if (get_cmd_type(&line[1]) == 2 || get_cmd_type(&line[1]) == 3
				|| get_cmd_type(&line[1]) == 5 || get_cmd_type(&line[1]) == 7)
			{
				good = 1;
				break ;
			}
		}
		if (*line == '(')
			parenthesis++;
		if (*line == ')')
			parenthesis--;
		line++;
	}
	if (good == 1 || parenthesis != 0)
	{
		if (good == 1)
			printf("parse error near '%c'\n", *line);
		else if (parenthesis != 0)
			printf("missing parenthesis\n");
		free(bak);
		bak = NULL;
	}
	return (bak);
}

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
			title = ft_strjoin("\e[1;32mminishell-0.2\e[0m:\e[1;34m~", &path[i]);
		else
			title = ft_strjoin("\e[1;32mminishell-0.2\e[0m:\e[1;34m", path);
	}
	else
		title = ft_strjoin("\e[1;32mminishell-0.2\e[0m:\e[1;34m", path);
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
		else if (shell->line == NULL)
			return (0);
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

	shell->line = test_line(shell->line);
	line = parse_space(shell->line);
	if (line == NULL)
		return (shell->return_err = 1);
	free(shell->line);
	shell->line = line;
	shell->tree = bt_create(shell->line);
	put_last_tree(shell->tree);
	pre_prepare_exec(shell, shell->tree);
	wait_process(shell->tree, shell);
	close_all_fd(shell->tree);
	free_bt(shell->tree);
	shell->tree = NULL;
	return (0);
}

/* ----------------------| LAST!!! |----------------------- */
/*	Search the last execution and set variable last to 1.	*/
/*	That can be more last to one.. Need check if the first	*/
/*	node is || or &&										*/
/* -------------------------------------------------------- */
void	put_last_tree(t_tree *tree)
{
	if (tree->type == 2 || tree->type == 3)
	{
		put_last_tree(tree->left);
		put_last_tree(tree->right);
		return ;
	}
	while (tree->right != 0)
		tree = tree->right;
	tree->last = 1;
}
