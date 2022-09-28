/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 08:33:06 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 21:17:01 by stissera         ###   ########.fr       */
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
		if (str != NULL && (*str == '\'' || *str == '"'))
		{
			quotes = *str++;
			while (*str != quotes)
				str++;
			str++;
			continue ;
		}
		if (str && *str != 0 && *str != 32
			&& *str != '\'' && *str != '"')
				str++;
		if (*str != 0 && *str == ' ' && *++str != 0 && ret++)
			str = ft_skipspace(str);
	}
	ret++;
	return (ret);
}

static char	*ft_write_argv(char *str, char **new, size_t index)
{
	size_t	i;
	size_t	write;
	char	quotes;
	char	*ret;

	i = 0;
	write = 0;
	while (str[i] && str[i] != 0 && str[i] != ' ')
	{
		while (str[i] != 0 && str[i] != 32
			&& (str[i] == '"' || str[i] == '\''))
		{
			quotes = str[i++];
			while (str[i] != 0 && str[i] != quotes)
				i++;
			i++;
		}
		while (str[i] != 0 && str[i] != 32
			&& (str[i] != '"' || str[i] != '\''))
			i++;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		exit (0);
	while (write < i)
	{
		while (str[i] != 0 && str[i] != 32
			&& (str[i] == '"' || str[i] == '\''))
		{
			quotes = *str++;
			while (*str != 0 && *str != quotes)
				ret[write++] = *str++;
			if (*str != 0)
				ret[write++] = *str++;
		}
		while (*str != 0 && *str != 32
			&& (*str != '"' || *str != '\''))
			ret[write++] = *str++;
	}
	ret[write] = 0;
	new[index] = ret;
	return (str);
}

static char	**split_param(char **param, size_t i, char quote)
{
	char	**ret;
	size_t	param_i;
	size_t	count;

	count = 0;
	param_i = 0;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		exit(ft_exit(errno, 0));
	ft_tabbzero(ret, i);
	ret[count++] = ft_strdup(param[param_i++]);
	while (count < i)
	{
		ret[count] = NULL;
		while (*param[param_i] != 0)
		{
			if (*param[param_i] != 0 && (*param[param_i] == '\''
					|| *param[param_i] == '"'))
			{
				quote = *param[param_i]++;
				while (*param[param_i] != 0 && *param[param_i] != quote)
					ret[count] = ft_joincts(ret[count], *param[param_i]++)
						+ free_str(ret[count]);
				param[param_i]++;
				continue ;
			}
			if (*param[param_i] != 0 && *param[param_i] != ' ')
			{
					ret[count] = ft_joincts(ret[count], *param[param_i]++)
					+ free_str(ret[count]);
			}
			if (*param[param_i] != 0 && *param[param_i] == ' '
				&& param[param_i]++)
				count++;
		}
		param_i++;
		count++;
	}
	return (ret);
}

static char	**explose_param(char **param)
{
	size_t	nbr_param;
	size_t	i;
	size_t	p;
	char	quote;

	nbr_param = 0;
	i = 0;
	p = 0;
	while (param[i] != NULL && param[i] != 0)
	{
		while (param[i][p] != 0)
		{
			if (param[i][p] != 0 && (param[i][p] == '\'' || param[i][p] == '"'))
			{
				quote = param[i][p++];
				while (param[i][p] != 0 && param[i][p] != quote)
					p++;
				p++;
			}
			while (param[i][p] != 0 && param[i][p] != ' ' && param[i][p] != '\''
				&& param[i][p] != '"')
				p++;
			if (param[i][p] != 0 && param[i][p] == ' ' && p++)
				nbr_param++;
		}
		nbr_param++;
		p = 0;
		i++;
	}
	return (split_param(param, nbr_param, 0));
}

char	**param_to_exec(char *str, char *name)
{
	char	**ret;
	size_t	i;
	size_t	count;

	count = 1;
	i = 0;
	ret = NULL;
	count += ft_countav(str);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ret)
		exit(ft_exit(errno, 1));
	ft_tabbzero(ret, count);
	ret[i] = ft_strdup(name);
	if (count == 1)
		return (ret);
	while (++i < count)
	{
		str = ft_skipspace(str);
		str = ft_write_argv(str, ret, i);
		ret[i] = checkstar(ret[i]) + free_str(ret[i]);
	}
	return (explose_param(ret));// + free_tab(ret));
}
