/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/07/11 22:13:08 by stissera         ###   ########.fr       */
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

int	w_history(char **history)
{
	int	history_fd;

	if (!check_auth("./", FILE_HISTORY))
		return (msg_err(ACCESS_ERR));
	history_fd = open("./.minishell_history", O_CREAT | O_RDWR | O_APPEND);
	if (history_fd < 0)
		return (history_fd);

	return (1);
}

int	welcome(void)
{
	int		welcome_msg;
	char	*str;

	welcome_msg = open("modt.txt", O_RDONLY);
	if (welcome_msg < 0)
	{
		write(STDOUT, "Welocome to minishell\n You can create your \
			own welcome message with modt.txt", 77);
		return (0);
	}
	else
	{
		while (read(welcome_msg, str, 1))
			write(STDOUT, str, 1);
		return (0);
	}
	return (1);
}
