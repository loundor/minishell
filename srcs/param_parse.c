/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:35:56 by stissera          #+#    #+#             */
/*   Updated: 2022/07/25 16:22:10 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* static char	*search_var(char *var)
{
	char	*ret;

	ret = NULL;
	(void)var;
	return (ret);
} */

static char	*take_single_quote(t_pparams *param)
{
	char	*line;
	size_t	start;
	size_t	end;
	size_t	len;

	end = 0;
	line = NULL;
	len = 0;
	start = -1;
	param->old++;
	while (param->old[end] != '\'')
		end++;
	if (end == 0)
		return (param->line);
	if (param->line)
		len = ft_strlen(param->line);
	line = (char *)malloc(sizeof(char) * (len + end + 1));
	if (!line)
		exit(ft_exit(MALLOCERR, 1));
	if (param->line)
	{
		if (*param->line)
			while (param->line[++start])
				line[start] = param->line[start];
		start = 0;
		while (start++ <= (end + len))
			line[start + ft_strlen(line)] = \
				param->old[start - ft_strlen(param->line)];
		line[ft_strlen(line) + end] = '\0';
	}
	else
	{
		while (++start <= end)
			line[start] = param->old[start];
		line[end] = '\0';
	}
	param->old = &param->old[end + 1];
	free (param->line);
	return (line);
}

static char	*take_double_quote(t_pparams *param)
{
	(void) param;
	write (1, "NEW IS NEW $\n", 12);
	return (param->line);
}

static char	*take_dollar(t_pparams *param)
{
	(void) param;
	write (1, "NEW IS NEW $\n", 12);
	return (param->line);
}

/* ---------------| PARAMETER PARSSING |------------------- */
/*	Get the pointer of cmd->param. Of every caractere check	*/
/*	if it's a signle or double quote and launch the funct	*/
/*	if need. Recept the new created line, and free the last	*/
/*	linenbak 0 -> parssing str								*/
/*	linenbak 1 -> str to parsse								*/
/* -------------------------------------------------------- */
char	*param_parse(t_cmd *cmd)
{
	t_env		*env;
	t_pparams	*param;

	(void)env;
	param = (t_pparams *)malloc(sizeof(t_pparams));
	if (!param)
		exit(ft_exit(MALLOCERR, 1));
	param->old = cmd->param;
	param->line = NULL;
	env = struct_passing(2, 0);
	while (*param->old)
	{
		if (*param->old == '\"')
			param->line = take_double_quote(param);
		else if (*param->old == '$' && *param->old != ' ')
			param->line = take_dollar(param);
		else if (*param->old == '\'')
			param->line = take_single_quote(param);
// fonction was just create ft_joincts. need test if work properly!!
		else
		{
ft_putstr_fd(param->line, 1);
			param->line = ft_joincts(param->line, (char)param->old[0]);
			param->old++;
		}
	}
	param->old = NULL;
	free(cmd->param);
	return (param->line);
}
