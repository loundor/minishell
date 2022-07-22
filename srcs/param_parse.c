/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:35:56 by stissera          #+#    #+#             */
/*   Updated: 2022/07/22 15:58:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*take_simple_quote(char *old, char *new)
{
	if (new)
		write (1, "NEW IS NEW\n", 12);
	return (old);
}

static char	*take_double_quote(char *old, char *new)
{
	if (new)
		write (1, "NEW IS NEW DC\n", 15);
	return (old);
}

static char	*search_var(char *var)
{
	char	*ret;

	ret = NULL;
	(void)var;
	return (ret);
}

char	*param_parse(t_cmd *cmd)
{
	t_env	*env;
	char	*bak[2];
	char	*new;

	bak[0] = cmd->param;
	env = struct_passing(2, 0);
	while (*cmd->param)
	{
		if (*cmd->param == '\'' || *cmd->param == '\"')
		{
			bak[1] = new;
			if (*cmd->param == '\'')
				new = take_simple_quote(cmd->param, new);
			else
				new = take_double_quote(cmd->param, new);
			free(bak[1]);
			continue ;
		}
		bak[1] = new;
// fonction was just create ft_joincts. need test if work properly!!		
		new = ft_joincts(new, (char)cmd->param);
		free(new);
	}
	free(bak[0]);
	return (new);
}
