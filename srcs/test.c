
#include "../includes/minishell.h"

int	test(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)((t_shell *)data)->cmd;
	write (1, "START OF TEST\n", 14);
	while (cmd != NULL)
	{
		printf("PATH: %s\nEXE: %s\nPARAM: %s\nTYPE: %d\n", cmd->path, cmd->command, cmd->param, cmd->type);
		cmd = cmd->next;
	}
	write (1, "END OF TEST\n", 12);
	write (1, "TEST env_to_exec\n", 17);
	char	**test;
	char	**bak;

	test = env_to_exec();
	bak = test;
	while (test && *test)
		puts(*test++);
	free (bak);
	write (1, "END OF TEST\n", 12);
	return (0);
}
