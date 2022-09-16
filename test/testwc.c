#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	(void)ac;
	while (*av != NULL)
	{
		puts(*av);
		av++;
	}
	return 0;
}