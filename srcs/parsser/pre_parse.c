/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/08/29 14:44:48 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*write_quotes(char *line, char *ret, size_t *i)
{
	if (*line == '"' || *line == '\'')
	{
		if (*line == '"')
		{
			ret[(*i)++] = *line++;
			while (*line != '"')
				ret[(*i)++] = *line++;
		}
		else if (*line == '\'')
		{
			ret[(*i)++] = *line++;
			while (*line != '\'')
				ret[(*i)++] = *line++;
		}
			ret[(*i)++] = *line++;
		if (ret[*i] == '"' || *ret == '\'')
			ret = write_quotes(line, ret, i);
	}
	return (line);
}

static char	*write_parse_space(char *line, size_t i)
{
	char	*ret;

	ret = NULL;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line && *line != 0)
	{
		line = write_quotes(&*line, ret, &i);
		if (*line == ' ')
		{
			ret[i] = *line++;
			while (line && *line == ' ')
				line++;
		}
		else if (*line == 0)
			continue ;
		else
			ret[i] = *line++;
		// dans le else il faut egalement verifier les separateurs
		// Si un separateur est present, verifier qu il y a bien
		// un espace avant et apres, sinon les ajouter et deplacer
		// le pointeur et incrementer i * continue...
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*count_quotes(char *ret, size_t *i)
{
	if (*ret == '"' || *ret == '\'')
	{
		if (*ret == '"')
		{
			*i = *i + 1;
			while (*++ret != '"')
				*i = *i + 1;
		}
		else if (*ret == '\'')
		{
			*i = *i + 1;
			while (*++ret != '\'')
				*i = *i + 1;
		}
		*i = *i + 1;
		if (*++ret == '"' || *ret == '\'')
			ret = count_quotes(ret, i);
	}
	return (ret);
}

char	*parse_space(char *line)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (*line == '\0')
		return (NULL);
	ret = ft_skipspace(line);
	while (ret && *ret != 0)
	{
		ret = count_quotes(ret, &i);
		// ajouter le test des separateurs (|, &, <....) avec verification des
		// espaces avant et apres.. si il n y a pas d espaces, incrementer la
		// variable i. Deplacer egaelent le pointeur puis faire un continue.
		//	Attention retravailler le write_parse_space pour ajouter les
		// espaces au besoin!!!
		if (*ret == ' ')
		{
			i++;
			while (ret && *ret == ' ')
				ret++;
			continue ;
		}
		i++;
		if (ret && *ret == 0)
			break ;
		ret++;
	}
	ret = write_parse_space(ft_skipspace(line), i);
	return (ret);
}
