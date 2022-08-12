/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:42:02 by stissera          #+#    #+#             */
/*   Updated: 2022/08/12 20:16:44 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_skipspace(char *str)
{
	char	*ret;

	if (!str || *str == '\0')
		return (0);
	ret = str;
	while (*ret && (*ret == '\t' || *ret == '\n' || *ret == '\v'
			|| *ret == '\f' || *ret == '\r' || *ret == ' '))
		ret++;
	if (*ret == '\0')
		return (0);
	return (ret);
}

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
		else
			ret[i] = *line++;
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
//	if (ret[-1] && ret[-1] == ' ')
//		i--;
	ret = write_parse_space(ft_skipspace(line), i);
	return (ret);
}

int main()
{
    char    test[] = "    test1   test2&&    (   test3 \"   ) test4    \"  )   ||'    test5 \"  test6  \"  |  test7   '  >    test8   >> test9      <<    test 10      ";
    // Total: 150
// test1 test2 && ( test3 "   ) test4    " ) || '    test5 "  test6  "  |  test7   ' > test8 >> test9 << test 10
    // Should: 111
    char    *line;

    line = NULL;
    line = parse_space(test);
    printf("%s", line);
    return (0);
}
