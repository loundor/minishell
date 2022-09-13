/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 08:33:06 by stissera          #+#    #+#             */
/*   Updated: 2022/09/12 11:52:46 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ----------------| DO ARGV FOR EXECVE |------------------ */
/*	Take the line param et slpit in a array like argv.		*/
/*	WARNING! The first index (0) stay null. We need to		*/
/*	implement the name of the executable in parent function	*/
/* -------------------------------------------------------- */

static size_t	ft_countav(char *str)
{
	size_t	ret;
	char	quotes;

	ret = 0;
	str = ft_skipspace(str);
	while (str && *str != 0)
	{
		str = ft_skipspace(str);
		while (str && *str != 0 && *str != 32 && *str != '\'' && *str != '"')
			str++;
		ret++;
		str = ft_skipspace(str);
		if (!str || *str == 0)
			return (ret);
		if (*str == 32)
			continue ;
		if (*str == '\'' || *str == '"')
		{
			quotes = *str;
			str++;
			while (*str != quotes)
				str++;
			str++;
			continue ;
		}
	}
	return (ret);
}

static char	*ft_write_argv(char *str)
{
	size_t	i;
	size_t	write;
	char	quotes;
	char	*ret;

	i = 0;
	write = 0;
	str = ft_skipspace(str);
	if (str[i] == '"' || str[i] == '\'')
	{
		quotes = str[i++];
		while (str[i] != quotes)
			i++;
		i++;
	}
	else if (str[i] && str[i] != 32)
	{
		while (str[i] != 0 && str[i] != ' ')
			i++;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		exit (0);
	while (write < i)
	{
		ret[write++] = *str;
		str++;
	}
	ret[write] = 0;
	return (ret);
}

char	**param_to_exec(char *str, char *name)
{
	char	**ret;
	size_t	i;
	size_t	count;
	char	quotes;

	count = 1;
	i = 0;
	ret = NULL;
	count += ft_countav(str);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ret)
		exit(0);
	ret[0] = ft_strdup(name);
	ret[count] = NULL;
	if (count == 1)
		return (ret);
	while (++i < count)
	{
		ret[i] = ft_write_argv(str);
		str = ft_skipspace(str);
		if (*str == '"' || *str == '\'')
		{
			quotes = *str++;
			while (*str != quotes)
				str++;
			str++;
			continue ;
		}
		else if (str && *str != 32)
		{
			while (*str != 0 && *str != ' ')
				str++;
		}
	}
	return (ret);
}
