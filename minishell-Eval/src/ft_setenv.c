/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/24 00:11:21 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_setenv(char **ev, char ***var, char ***his)
{
	size_t	size;
	char	**addr;
	char	*buf;

	*var = ft_init_var();
	if (!*var || ft_stdio(SAVE_IO))
		return ((char **)0);
	*his = ft_calloc(1, sizeof (char *));
	if (!*his)
		return ((char **)(size_t)ft_sfree(*var));
	if (ft_gethis(getenv("HOME"), HISTORY))
		ft_errmsg(-8 + (0 * ft_errmsg(errno)));
	ev = ft_strtdup(ev);
	if (!ev)
		return ((char **)(size_t)(ft_sfree(*his) * ft_sfree(*var)));
	addr = ft_isvarin("SHLVL=", ev);
	buf = ft_itoa(ft_atoi(*addr + 6) + 1);
	if (!buf)
		return ((char **)(size_t)(ft_sfree(*his) * ft_sfree(ev) *
			ft_sfree(*var)));
	size = ft_strlen(buf) + ft_free(*addr);
	*addr = ft_calloc(size + 7, sizeof (char));
	ft_strlcpy(*addr, "SHLVL=", size + 7);
	ft_strlcpy(*addr + 6, buf, size + 1);
	return (ev + ft_free(buf));
}
