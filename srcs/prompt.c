/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/07/25 07:07:42 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* -----------------| WRITE WHAT YOU WANT! |--------------- */
/*	After initialisation, write create the prompt.			*/
/*	The prompt wait until the command is validate, check	*/
/* the command is not null and put the command line in core	*/
/* -------------------------------------------------------- */
int	prompt(t_shell *shell)
{
	char	*line;

	while (!shell->line || strcmp(shell->line, "exit"))
	{
		shell->cmd = NULL;
		if (shell->line != NULL)
			free(shell->line);
		shell->line = readline("\e[36mminishell-0.1$\e[0m ");
		line = shell->line;
		line = ft_skipspace(line);
		if (line)
		{
			if (core(shell))
				printf("An error was occured!\n");
		}
		else
			continue ;
		add_history(shell->line);
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

	shell->cmd = cmd_parse(shell->line, shell->cmd);
	builtin = search_builtin(shell->cmd->command, shell->builtin);
printf("-->%s<--", shell->cmd->command);
	if (builtin != NULL)
		builtin->f(shell);
	return (0);
}
