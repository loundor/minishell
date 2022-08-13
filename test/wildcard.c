#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int	starcmp(char *pattern, char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (1);
	if (*pattern == '?' || *pattern == *string)
		return (starcmp(pattern + 1, string + 1));
	if (*pattern == '*')
		return (starcmp(pattern + 1, string) || starcmp(pattern, string + 1));
	return (0);
}

int	main(int argc, char **argv)
{
	DIR				*path;
	struct dirent	*inside;

	(void)argc;
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
}
