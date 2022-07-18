#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (void)
{
	char	*env;

	env = getenv();
	puts(env);
}
