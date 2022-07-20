
#include "../includes/minishell.h"

int	test(void *data)
{
	write (1, "START OF TEST\n", 14);
(void)data;
	write (1, "END OF TEST\n", 12);
	return (0);
}
