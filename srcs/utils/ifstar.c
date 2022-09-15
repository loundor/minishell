/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifstar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:07:31 by stissera          #+#    #+#             */
/*   Updated: 2022/09/15 19:55:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


///// NEED SPLIT RET TO DO ONE ARGV PRO TAB. LIKE ARGV
static char	*get_list(char *dir, char *pattern, int root, char *ret)
{
	t_wildcard		wildcard;
	struct dirent	*inside;
	DIR				*path;
	char			*newdir;

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
		if (ret != NULL && inside->d_type == DT_REG && starcmp(&wildcard))
		{
			ret = ft_strjoin(ret, " ") + free_str(ret);
			ret = ft_strjoin(ret, wildcard.str) + free_str(ret);
		}
		if (ret == NULL && inside->d_type == DT_REG && starcmp(&wildcard))
			ret = ft_strdup(wildcard.str);
		if (inside->d_type == DT_DIR && root == 1 && starcmp(&wildcard))
		{
			newdir = ft_strjoin(dir, inside->d_name);
			ret = get_list(newdir, "*", 0, ret) + free_str(ret);
		}
	inside = readdir(path);
	}
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
	return (get_list(dir, pattern, 1, (void *) 0)
		+ free_str(pattern) + free_str(dir));
}

char	*checkstar(char *av)
{
	size_t	i;

	i = 0;
	if (av == NULL || av[1] == '"' || av[1] == '\'')
		return (av);
	while (av[i] != 0)
	{
		if (av[i] == '?' || av[i] == '*')
			return (remplace_star(av, i));
		i++;
	}
	return (av);
}
