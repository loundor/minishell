/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/08/03 21:53:13 by stissera         ###   ########.fr       */
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

// ATTENTION SI LE DEBUT DE CMD EST " OU ' ET QU UN ESPACE EST PRESENT DEDANS
// LA COMMANDE NE SERA PAS CORRECT ET LA PARTIE APRES L ESPACE SE RETROUVERA
// DANS LES PARAMM!!!
	line = line_parse(shell->line);
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
