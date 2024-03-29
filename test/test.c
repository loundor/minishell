#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

static char	*ft_skipspace(char *str)
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
	return (&*ret);
}

static size_t ft_countav(char *str)
{
	size_t	ret;
	char	quotes;

	ret = 0;
	str = ft_skipspace(str);
	while (str && *str != 0)
	{
		str = ft_skipspace(str);
		while (*str != 0 && *str != 32 && *str != '\'' && *str != '"')
			str++;
		ret++;
		if (*str == 0)
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

char	**param_to_exec(char *str)
{
	char	**ret;
	size_t	i;
	size_t	count;
	char	quotes;

	count = 1;
	i = 0;
	ret = NULL;
	count += ft_countav(str);
	ret = (char **)malloc(sizeof(char *) * count);
	if (!ret)
		exit(0);
	ret[0] = NULL;
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

int main (void)
{
	char	test[] = "Voila une chaine \" qui devrait etre\" splited! mais sa marche pas";
	char	**ret = param_to_exec(test);
	//char	*name = "TEST";
	int		i = 1;
//	ret[0] = name;
	while (ret[i])
		printf("-->%s<--", ret[i++]);
	return 0;
}
