/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:35:56 by stissera          #+#    #+#             */
/*   Updated: 2022/07/25 07:05:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*search_var(char *var)
{
	char	*ret;

	ret = NULL;
	(void)var;
	return (ret);
}

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

static char	*take_dollar(char *old, char *new)
{
	char	*ret;
	char	*var;

	(void)ret;
	var = NULL;
	ret = search_var(var);
	if (new)
		write (1, "NEW IS NEW $\n", 12);
	return (old);
}

/* ---------------| PARAMETER PARSSING |------------------- */
/*	Get the pointer of cmd->param. Of every caractere check	*/
/*	if it's a signle or double quote and launch the funct	*/
/*	if need. Recept the new created line, and free the last	*/
/* -------------------------------------------------------- */
char	*param_parse(t_cmd *cmd)
{
	t_env	*env;
	char	*bak[2];
	char	*new;

	bak[0] = cmd->param;
	env = struct_passing(2, 0);
	while (*cmd->param)
	{
		if (*cmd->param == '\'' || *cmd->param == '\"'
			|| *cmd->param == '$')
		{
			bak[1] = new;
			if (*cmd->param == '\'')
				new = take_simple_quote(cmd->param, new);
			else if (*cmd->param == '\"')
				new = take_double_quote(cmd->param, new);
			else
				new = take_dollar(cmd->param, new);
			free(bak[1]);
			continue ;
		}
		bak[1] = new;
// fonction was just create ft_joincts. need test if work properly!!		
		new = ft_joincts(new, (char)cmd->param[0]);
		free(bak[1]);
	}
	free(bak[0]);
	(void)env;
	return (new);
}
