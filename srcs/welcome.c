/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:08:54 by stissera          #+#    #+#             */
/*   Updated: 2022/07/18 11:42:01 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_welcome(int *fd, int *file)
{
	int	i;
	int	*output;

	i = 0;
	output = fd;
	while (i++ < 2)
	{
		write(*output, "\
	___  ____       _     _          _ _\n\
	|  \\/  (_)     (_)   | |        | | |\n\
	| .  . |_ _ __  _ ___| |__   ___| | |\n\
	| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n\
	| |  | | | | | | \\__ \\ | | |  __/ | |\n\
	\\_|  |_/_|_| |_|_|___/_| |_|\\___|_|_|\n\
			afuchs & stissera - v0.1\n", 261);
		if (i == 1 && output != file)
			write (*output, "\nA new file named modt was created\
on minishell directory.\n You can modify the file to see a new welcome\
page.\n", 110);
		output = file;
	}
}

int	welcome(void)
{
	int		welcome_msg;
	char	str[1];
	int		output;

	str[0] = 0;
	welcome_msg = open("modt", O_RDONLY);
	output = STDOUT;
	if (welcome_msg < 0)
	{
		welcome_msg = open("modt", O_CREAT | O_WRONLY, 0644);
		print_welcome(&output, &welcome_msg);
		close(welcome_msg);
		return (0);
	}
	else
	{
		while (read(welcome_msg, str, 1) > 0)
		{
			write(STDOUT, str, 1);
		}
		return (0);
	}
	return (1);
}
