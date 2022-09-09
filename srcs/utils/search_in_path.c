/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:54:29 by stissera          #+#    #+#             */
/*   Updated: 2022/09/09 13:41:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_in_path(char *command, char *env)
{
	char	**path;
	int		i;
	char	*pathname;

	i = 0;
	pathname = NULL;
	if (env == NULL)
		return (pathname);
	path = ft_split(env, ':');
	while (path[i] && path[i] != 0)
	{
		pathname = (char *)malloc(sizeof(char)
				* (ft_strlen(path[i]) + ft_strlen(command) + 2));
		ft_strlcpy(pathname, path[i],
			ft_strlen(path[i]) + ft_strlen(command) + 2);
		ft_strlcpy(pathname + ft_strlen(path[i]),
			"/", ft_strlen(command) + 2);
		ft_strlcpy(pathname + ft_strlen(path[i]) + 1,
			command, ft_strlen(command) + 1);
		if (!access(pathname, F_OK) || (free_str(pathname)))
			return (pathname + free_tab(path) + free_str(env));
		i++;
	}
	pathname = NULL;
	return (pathname + free_tab(path) + free_str(env));
}
