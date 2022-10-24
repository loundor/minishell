/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exicmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:22:31 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 15:40:54 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_exicmd(char **av, char *last_status)
{
	int	len;

	len = ft_strtlen(av);
	if (len > 2)
		return ((1 << 8) + (0 * ft_putstr_l("Error: too many arguments\n", 2)));
	if (len > 1)
		return (0 * ft_exit_toggle(SAVE_HISTORY, *(av + 1), 0));
	return (0 * ft_exit_toggle(SAVE_HISTORY, last_status, 0));
}
