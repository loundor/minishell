/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifstar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:07:31 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 21:13:24 by stissera         ###   ########.fr       */
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
			&& ft_strncmp("..", inside->d_name, 3) && starcmp(&wildcard))
		{
			if (strncmp(dir, "./", 3))
				ret = ft_strdup(dir);
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
		return (av + (0 * printf("Wildcard only on working folder!\n")));
	while (av[i] != '/' && i != 0)
			i--;
	if ((i > 0 && i++) || (av[i] == '/' && i++) || i == 0)
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

static char	*pattern_write(char *av)
{
	size_t	i;
	char	*str;

	i = 0;
	while (av[i] != 0)
	{
		if (av[i] == '?' || av[i] == '*')
		{
			str = remplace_star(av, i);
			if (str == av || str == NULL || str == 0)
				return (av);
			return (str + free_str(av));
		}
		i++;
	}
	return (av);
}

static int	is_needsearch(char *av)
{
	char	quotes;

	while (*av != 0)
	{
		if (*av == '\'' || *av == '"')
		{
			quotes = *av++;
			while (*av != 0 && *av != quotes)
				av++;
		}
		if (*av != 0 && *av == '*')
			return (1);
		if (*av != 0)
			av++;
	}
	return (0);
}

char	*checkstar(char *av)
{
	size_t	i;
	char	*pattern;
	char	quote;
	char	*home;

	if (!av || av == 0 || av == NULL)
		return (ft_strdup(av));
	i = 0;
	pattern = NULL;
	home = NULL;
	if (av[0] == '~')
	{
		home = search_var("HOME");
		if (home != NULL && av++)
			av = ft_strjoin(home, av);
	}
	if (!is_needsearch(av))
		return (ft_strdup(av) + free_str(home));
	while (av[i] != 0)
	{
		while (av[i] != 0 && av[i] != '\'' && av[i] != '"')
			pattern = ft_joincts(pattern, av[i++]) + free_str(pattern);
		if (av[i] != 0 && (av[i] == '\'' || av[i] == '"'))
		{
			quote = av[i++];
			while (av[i] != 0 && av[i] != quote)
			{
				if (av[i] == '*' || av[i] == '?' )
				{
					if (home != NULL)
						return (ft_strjoin(home, av) + free_str(pattern)
							+ free_str(home));
					else
						return (ft_strdup(av) + free_str(pattern));
				}
				pattern = ft_joincts(pattern, av[i++]) + free_str(pattern);
			}
			if (av[i] != 0)
				i++;
			continue ;
		}
	}
	return (pattern_write(pattern) + free_str(home));
}
