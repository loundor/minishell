/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 08:33:06 by stissera          #+#    #+#             */
/*   Updated: 2022/09/16 10:58:54 by stissera         ###   ########.fr       */
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
	if (!str || str == 0)
		return (ret);
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

static char	**split_param(char **param, size_t i)
{
	char	**ret;
	char	**split;
	size_t	param_i;
	size_t	count;
	size_t	e;

	count = 0;
	e = 0;
	param_i = 0;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		exit(ft_exit(errno, 0));
	ret[i] = NULL;
	ret[count++] = ft_strdup(param[param_i++]);
	while (param[param_i] && count <= i)
	{
		if ((*param[param_i] != '\'' || *param[param_i] != '"'
				|| *param[param_i] != '$'))
		{
			split = ft_split(param[param_i++], ' ');
			while(split[e] != 0)
				ret[count++] = ft_strdup(split[e++]);
			free_tab(split);
			e = 0;
			continue ;
		}
		else
			ret[count] = ft_strdup(param[param_i]);
		param_i++;
		count++;
	}
	return(ret);
}

static char **explose_param(char **param)
{
	size_t	nbr_param;
	size_t	i;
	size_t	p;

	nbr_param = 0;
	i = 0;
	p = 0;
	while (param[i] != NULL)
	{
		if (param[i][p] == '\'' || param[i][p] == '"' || param[i][p] == '$')
		{
			nbr_param++;
			i++;
			continue ;
		}
		while (param[i][p] != 0)
			if (param[i][p++] == ' ')
				nbr_param++;
		nbr_param++;
		p = 0;
		i++;
	}
	return (split_param(param, nbr_param));
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
		ret[i] = checkstar(ret[i]);
	}
	return (explose_param(ret) + free_tab(ret));
}
