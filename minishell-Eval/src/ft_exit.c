/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:57:01 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 15:46:31 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_exit(char **ev, char **var, char **his)
{
	int	exit_status;

	if (ft_exit_toggle(STATE, (char *)0, &exit_status) != NO_SAVE_HISTORY)
		(void)ft_savhis(getenv("HOME"), HISTORY, his);
	ft_sfree(ev);
	ft_sfree(var);
	ft_sfree(his);
	ft_stdio(CLOSE_IO);
	ft_setio(CLOSE_IO);
	exit(exit_status);
}
