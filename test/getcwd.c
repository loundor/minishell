#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
int	main(void)
{
	char	ret[130];
	char	*ret2;

	ret2 = getcwd(ret, 130);
	printf("-->%s<--\n", ret);
	printf("-->%s<--\n", ret2);
	return 0;
}