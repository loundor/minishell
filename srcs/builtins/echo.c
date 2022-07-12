/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:05:06 by stissera          #+#    #+#             */
/*   Updated: 2022/07/12 17:39:39 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_echo(char *str, int fd)
{
	int	flgs;

	if (str[0] == '-' && str[1] == 'n' && str[2] == ' ')
	{
		flgs = 1;
		str = str[3];
		while (isspace(*str))
			str++;
	}
	while (*str || (*str != '\c' && flgs))
	{
		if (*str == 34)
			str = write_double_quote(*str++, fd, flgs);
		else if (*str == 47)
			str = write_simple_quote(*str++, fd, flgs);
		else
		{
			if (*str == '\n' && !flgs)
				write (fd, str, 1);
			str++;
		}
	}
}

char	*write_double_quote(char *str, int flgs)
{
	size_t	var_size;

	var_size = 0;
	while (*str != 34)
	{
		if (*str == '\0')
			return(wait_quote((char)34));
		if (*str == '$' && str[1] != '\\' )
		{
			while (str[i])
		}
	}
	return (str);
}