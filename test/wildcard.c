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
	while (test->pattern[test->ps] == test->str[test->ss]
		|| test->pattern[test->ps] == '?'
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
		while (test->str[test->se] == test->pattern[test->pe]
			&& test->pe >= test->ps)
		{
			test->pe--;
			test->se--;
		}
		if (test->str[++test->se] == test->pattern[++test->pe]
			&& test->pe == test->ps)
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

	bakp = test->pe - 1;
	baks = strlen(test->str) - 1; // Do ft_ !!!!
	count = baks;
	while (bakp > test->ps)
	{
		if (test->str[baks] == test->pattern[bakp])
		{
			bakp--;
			baks--;
			continue ;
		}
		baks = --count;
		bakp = test->pe - 1;
	}
	if (bakp == test->ps)
	{
		test->ss = baks;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_wildcard		test;
//	DIR				*path;
//	struct dirent	*inside;

	test.pattern = "?????e**********";
	test.str = "test1entretest2suitetest3";
	test.ss = 0;
	test.se = 0;
	test.pe = 0;
	test.ps = 0;
	puts(test.pattern);
	puts(test.str);
	printf("Valeur de retour sur wildcard: %d\n", starcmp(&test));
	return (0);
}

/* 	(void)argc;
	path = opendir(argv[1]);
	inside = readdir(path);
	puts("Nom   - Type");
	while (inside != NULL)
	{
		printf("%s  --  %d\n", inside->d_name, inside->d_type );
		inside = readdir(path);
	}
	if (starcmp("AllerEtC*he", "AllerEtCaMarche pas"))
		printf("Oui");
	else
		printf("Non");
	return (0);
} */
