/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/07/13 18:45:14 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = do_env(env);
	if (!shell.env)
		exit(ft_error(ENV));
	if (argc == 1)
		(void)argv;
	// Not already implemented..
/* 	else
	{
		commande_parse(**argv, shell);
		execute(shell);
		exit (ft_free_lvl(2));
	} */

	if (welcome() != 0)
		exit (ft_free_lvl(3));

	if (!prompt())
		return (0);
}
