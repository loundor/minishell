#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct s_wildcard
{
	char		*str;
	int			ss;
	int			se;
	char		*pattern;
	int			ps;
	int			pe;
}	t_wildcard;

int	part_wild_test(t_wildcard *test);
int	parse_wildcard(t_wildcard *test);

int	starcmp(t_wildcard	*test)
{
	test->se = strlen(test->str); // to ft_!!!
	while ((test->pattern[test->ps] == test->str[test->ss]
		|| test->pattern[test->ps] == '?')
		&& (test->pattern[test->ps] != 0 && test->str[test->ss] != 0))
	{
		test->ss++;
		test->ps++;
	}
	if (test->pattern[test->ps] == 0 && test->str[test->ss] == 0)
		return (1);
	if (test->pattern[test->ps] == '*')
	{
		while (test->pattern[test->ps] == '*')
			test->ps++;
		if (test->pattern[test->ps] == 0)
			return (1);
		return (parse_wildcard(test));
	}
	return (0);
}

int	parse_wildcard(t_wildcard *test)
{
	test->pe = test->ps;
	while (test->pattern[test->pe] != 0 && test->pattern[test->pe] != 42)
		test->pe++;
	if (test->pattern[test->pe] == 0)
	{
		while ((test->str[test->se] == test->pattern[test->pe]
				|| test->pattern[test->pe] == '?') && test->pe >= test->ps)
		{
			test->pe--;
			test->se--;
		}
		if ((test->str[++test->se] == test->pattern[++test->pe]
				|| test->pattern[++test->pe] == '?') && test->pe == test->ps)
			return (1);
		return (0);
	}
	if (part_wild_test(test))
	{
		if (test->se != test->ss)
			return (starcmp(test));
		return (0);
	}
	return (0);
}

int	part_wild_test(t_wildcard *test)
{
	int	bakp;
	int	baks;
	int	count;

	bakp = test->ps;
	baks = test->ss;
	count = baks;
	while (baks < test->se && bakp < test->pe)
	{
		if (test->str[baks] == test->pattern[bakp]
			|| test->pattern[bakp] == '?')
		{
			bakp++;
			baks++;
			continue ;
		}
		baks = ++count;
		bakp = test->ps;
	}
	if (bakp >= test->ps)
	{
		test->ss = count;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_wildcard		test;
	DIR				*path;
	struct dirent	*inside;

	(void)argc;
	path = opendir(argv[1]);
	inside = readdir(path);
	test.pattern = argv[2];
	puts(test.pattern);
	while (inside != NULL)
	{
		if (inside->d_type == 8)
		{
			test.ss = 0;
			test.se = 0;
			test.pe = 0;
			test.ps = 0;
			test.str = inside->d_name;
			if (starcmp(&test))
				printf("%s\n", test.str);
		}
		inside = readdir(path);
	}
	return (0);
}
