/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/07/19 16:30:03 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt(t_shell *shell)
{
	while (!shell->line || strcmp(shell->line, "exit"))
	{
		shell->line = readline("minishell-0.1$ ");
		if (shell->line[0] != '\0')
			if (core(shell))
				printf("An error was occured!\n");
		add_history(shell->line);
	}
	write(STDOUT, "exit\n", 5);
	return (0);
}

int	core(t_shell *shell)
{
	t_builtins	*builtin;
	// DO PARSSING FROM shell->line to struct shell->cmd
	builtin = search_builtin(shell->line, shell->builtin);
	if (builtin != NULL)
		builtin->f(shell);
	return (0);
}
