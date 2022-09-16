/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifstar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:07:31 by stissera          #+#    #+#             */
/*   Updated: 2022/09/16 11:05:56 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_list(char *dir, char *pattern, char *ret)
{
	t_wildcard		wildcard;
	struct dirent	*inside;
	DIR				*path;

	path = opendir(dir);
	inside = readdir(path);
	wildcard.pattern = pattern;
	while (inside != NULL)
	{
		wildcard.ss = 0;
		wildcard.se = 0;
		wildcard.pe = 0;
		wildcard.ps = 0;
		wildcard.str = inside->d_name;
		if (ret != NULL && ft_strncmp(".", inside->d_name, 2)
			&& ft_strncmp("..", inside->d_name, 3) && starcmp(&wildcard))
		{
			ret = ft_strjoin(ret, " ") + free_str(ret);
			if (strncmp(dir, "./", 3))
				ret = ft_strjoin(ret, dir) + free_str(ret);
			ret = ft_strjoin(ret, wildcard.str) + free_str(ret);
		}
		if (ret == NULL && ft_strncmp(".", inside->d_name, 2)
			&& ft_strncmp("..", inside->d_name, 3)  && starcmp(&wildcard))
		{
			if (strncmp(dir, "./", 3))
				ret = ft_strdup(dir);;
			if (ret != NULL)
				ret = ft_strjoin(ret, wildcard.str) + free_str(ret);
			else
				ret = ft_strdup(wildcard.str);
		}
			
	inside = readdir(path);
	}
	closedir(path);
	return (ret);
}

static char	*remplace_star(char *av, size_t i)
{
	size_t	end;
	char	*pattern;
	char	*dir;

	end = ++i;
	while (av[end] != 0 && av[end] != '/')
		end++;
	if (av[end] == '/')
		return (av + (0 * printf("Wildcard only on selected folder!\n")));
	while (av[i] != '/' && i != 0)
			i--;
	if ((i > 0 && i++) || (av[i] == '/' && i++) || i == 0 )
		pattern = ft_strdup(&av[i]);
	if (i > 0)
	{
		dir = (char *)malloc(sizeof(char) * (i + 1));
		if (!dir)
			exit (ft_exit(errno, 1));
		dir[i] = 0;
		while (i != 0 && i--)
			dir[i] = av[i];
	}
	else
		dir = ft_strjoin(".", "/");
	return (get_list(dir, pattern, (void *) 0)
		+ free_str(pattern) + free_str(dir));
}

char	*checkstar(char *av)
{
	size_t	i;
	char	*str;

	i = 0;
	if (av == NULL || av[1] == '"' || av[1] == '\'')
		return (av);
	while (av[i] != 0)
	{
		if (av[i] == '?' || av[i] == '*')
		{
			str = remplace_star(av, i);
			if (str == av)
				return (av);
			return (str + free_str(av));
		}
		i++;
	}
	return (av);
}
