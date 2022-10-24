/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:01:01 by alfux             #+#    #+#             */
/*   Updated: 2022/10/05 16:00:03 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isdir(char const *file)
{
	struct stat	buf;

	if (!file || stat(file, &buf))
		return (-1);
	if ((buf.st_mode & S_IFDIR) == S_IFDIR)
		return (1);
	return (0);
}
