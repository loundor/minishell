/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/07/12 10:08:49 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	if (argc == 1)
		(void)argv;
	else
		create_command(argv, env);
	if (welcome() != 0)
		return (msg_err(WELCOME_ERR));
	if (!prompt())
		return (0);
}