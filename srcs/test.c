/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:04:56 by stissera          #+#    #+#             */
/*   Updated: 2022/09/01 17:05:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	// -------------------------------------------------------------------
	// ------------------------------- Wildcard --------------------------
	// -------------------------------------------------------------------
/* 	t_wildcard		tt;
	DIR				*path;
	struct dirent	*inside;

	path = opendir("./srcs");
	inside = readdir(path);
	tt.pattern = "*e.***c";
	puts(tt.pattern);
	while (inside != NULL)
	{
		if (inside->d_type == 8)
		{
			tt.ss = 0;
			tt.se = 0;
			tt.pe = 0;
			tt.ps = 0;
			tt.str = inside->d_name;
			if (starcmp(&tt))
				printf("%s\n", tt.str);
		}
		inside = readdir(path);
	} */

	// -------------------------------------------------------------------
	// ------------------------------- see struct cmd --------------------
	// -------------------------------------------------------------------
/* 	t_cmd	*cmd;

	cmd = (t_cmd *)((t_shell *)data)->cmd;
	write (1, "\nSTART OF TEST\n", 15);
	while (cmd != NULL)
	{
		printf("PATH: %s\nEXE: %s\nPARAM: %s\nTYPE: %d\n"
				, cmd->path, cmd->command, cmd->param, cmd->type);
		cmd = cmd->next;
	}
	write (1, "END OF TEST\n", 12); */

	// -------------------------------------------------------------------
	// ------------------------------- struct env to char ** -------------
	// -------------------------------------------------------------------
/* 	write (1, "TEST env_to_exec\n", 17);
	
	char	**test;
	char	**bak;

	test = env_to_exec();
	bak = test;
	while (test && *test)
		puts(*test++);
	free (bak);
	write (1, "END OF TEST\n", 12); */

int	test(void *data)
{
	(void)data;
	return (0);
}
