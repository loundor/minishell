#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
	int i[2];

	if (i[0] == 0)
		write(1, "OK\0", 3);
	return 0;
}
