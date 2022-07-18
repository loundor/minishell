/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:28 by stissera          #+#    #+#             */
/*   Updated: 2022/07/18 17:46:50 by stissera         ###   ########.fr       */
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
	// DO PARSSING FROM shell->line to struct shell->cmd
	if (!ft_strncmp(shell->line, "pwd", 3))
		pwd(shell);
	else if (!ft_strncmp(shell->line, "env", 3))
		env(shell);
	//puts(shell->line);
	return (0);
}
