/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/07/17 16:57:22 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = do_env(env);
	if (!shell.env)
		exit(ft_exit(ENV, 0, NULL));
	if (argc == 1)
		(void)argv;
	if (prep_signal(&shell))
		exit(ft_exit(SIGN, 0, NULL));
	// Not already implemented..
/* 	else
	{
		commande_parse(**argv, shell);
		execute(shell);
		exit (ft_free_lvl(2));
	} */

	if (welcome() != 0)
		exit (ft_exit(WELCOME_ERR, 1, &shell.env));

	if (!prompt(&shell))
		return (0);
	return (ft_exit(WELCOME_ERR, 9, &shell));
}
