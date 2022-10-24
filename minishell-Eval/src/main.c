/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 05:48:28 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_core(char **av, char ***ev, char ***var)
{
	int	exit_status;
	int	syntax;

	exit_status = 0;
	syntax = 0;
	if (!av)
		return (1 + (0 * ft_errmsg(errno)));
	syntax = ft_syntax_err(av);
	if (!syntax || 0 * ft_setint(&exit_status, -258))
		exit_status = ft_macro_exec(av, ev, var);
	**var = ft_extsta(exit_status, **var);
	if (syntax)
		return (0);
	if (ft_stdio(RESET_IO))
		return (1 + (0 * ft_errmsg(errno)));
	if (ft_exit_toggle(STATE, 0, 0))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	static char	*prompt;
	static char	**cmd;
	static char	**var;
	static char	**his;

	ev = ft_setenv(ev, &var, &his);
	if (!ev || !ac || !av || ft_sighdl(HDL_IGNORE_SIGQUIT | HDL_IGNORE_SIGINT))
		return (ft_errmsg(errno));
	prompt = ft_prompt(ev, &his + ft_errno(0));
	while (prompt)
	{
		cmd = ft_tknize(prompt);
		(void)ft_free(prompt);
		if (ft_core(cmd, &ev, &var) && !ft_sfree(cmd))
			break ;
		(void)ft_sfree(cmd);
		prompt = ft_prompt(ev, &his + ft_errno(0));
	}
	ft_exit(ev, var, his);
	return (ft_errmsg(errno));
}
