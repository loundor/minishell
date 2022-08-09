/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:42:02 by stissera          #+#    #+#             */
/*   Updated: 2022/08/09 23:11:19 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
    if (line[i - 1] == ' ')
        ret[i] = '\0';
    else
        ret[i] = '\0';
    return (ret);
}

char    *parse_space(char *line)
{
    char    *ret;
    size_t  i;

    ret = NULL;
    i = 0;
    line = ft_skipspace(line);
    if (*line == '\0')
        return (NULL);
    ret = line;
    while (ret && *ret != 0)
    {
        if (*ret == ' ')
        {
            i++;
            while (*ret == ' ')
                ret++;
        }
        i++;
        ret++;
    }
    if (ret[-1] && ret[-1] == ' ')
        i--;
    ret = write_parse_space(line, i);
    return (ret);
}

int main(int argc, char **argv)
{
    (void)argc;
    char    *line;

    line = NULL;
    line = parse_space(argv[1]);
    printf("%s", line);
    return (0);
}
