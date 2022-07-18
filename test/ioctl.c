#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

int main (void)
{
	int	*ioc;
	int fd;

	ioc = ioctl(fd, int requête, ...);  
}
