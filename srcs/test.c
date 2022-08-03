
#include "../includes/minishell.h"

int	test(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)((t_shell *)data)->cmd;
	write (1, "START OF TEST\n", 14);
	while (cmd != NULL)
	{
		printf("PATH: %s\nEXE: %s\nPARAM: %s\n", cmd->path, cmd->command, cmd->param);
		cmd = cmd->next;
	}
	write (1, "END OF TEST\n", 12);
	return (0);
}
