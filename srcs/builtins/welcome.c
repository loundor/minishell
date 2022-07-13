/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:08:54 by stissera          #+#    #+#             */
/*   Updated: 2022/07/13 18:45:02 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	welcome(void)
{
	int		welcome_msg;
	char	*str;
	int		output;
	int		i;

	welcome_msg = open("modt", O_RDONLY);
	output = STDOUT;
	i = 2;
	if (welcome_msg < 0)
	{
		print_welcome(output, welcome_msg);
		close(welcome_msg);
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

void	print_welcome(int *fd, int *file)
{
	int	i;
	int	*output;

	i = 0;
	output = fd;
	while (i++ != 0)
	{
		write(output, "___  ____       _     _          _ _\n\
		|  \/  (_)     (_)   | |        | | |\n\
		| .  . |_ _ __  _ ___| |__   ___| | |\n\
		| |\/| | | '_ \| / __| '_ \ / _ \ | |\n\
		| |  | | | | | | \__ \ | | |  __/ | |\n\
		\_|  |_/_|_| |_|_|___/_| |_|\___|_|_|\n\
							stissera - v0.1\n\
		\n A new file named modt was created on minishell directory.\n\
		You can modify the file to see a new welcome page.\0", 344);
		output = file;
	}
}
