/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:51 by stissera          #+#    #+#             */
/*   Updated: 2022/07/20 17:19:38 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	char	*buffer;
	size_t	size;

	size = 1;
	buffer = NULL;
	while (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * size);
		if (!buffer)
			ft_exit(MALLOCERR, 1);
		buffer = getcwd(buffer, size);
		if (buffer == NULL)
			free(buffer);
		size++;
	}
	ft_putendl_fd(buffer, 1); // ATTENTION TO FD!
	free (buffer);
	return (0);
}
