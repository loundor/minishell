
#include "../includes/minishell.h"

int	test(void *data)
{
	t_cmd	*cmd;
	t_tree	*tree;

	cmd = (t_cmd *)((t_shell *)data)->cmd;
	tree = (t_tree*)((t_shell *)data)->tree;
	write (1, "START OF TEST\n", 14);
	while (cmd != NULL)
	{
		printf("PATH: %s\nEXE: %s\nPARAM: %s\nTYPE: %d\n", cmd->path, cmd->command, cmd->param, cmd->type);
		cmd = cmd->next;
	}

printf("\n %p \n", tree);

	write (1, "END OF TEST\n", 12);
	return (0);
}
