/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:12:44 by stissera          #+#    #+#             */
/*   Updated: 2022/08/09 23:36:43 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *write_parse_space(char *line, size_t i)
{
    char    *ret;

    ret = NULL;
    ret = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (line && *line != 0)
    {
        if (*line == ' ')
        {
            ret[i] = *line++;
            while (*line == ' ')
                line++;
        }
        else
            ret[i] = *line++;
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char    *parse_space(char *line)
{
    char    *ret;
    size_t  i;

    ret = NULL;
    i = 0;
    if (*line == '\0')
        return (NULL);
    ret = ft_skipspace(line);
    while (ret && *ret != 0)
    {
        if (*ret == ' ')
        {
            i++;
            while (ret && *ret == ' ')
                ret++;
        }
        i++;
        if (ret && *ret == 0)
            break ;
        ret++;
    }
    if (ret[-1] && ret[-1] == ' ')
        i--;
    ret = write_parse_space(ft_skipspace(line), i);
    return (ret);
}
