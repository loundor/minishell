/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macro_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:36:36 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 15:11:36 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_to_next_logical_operator(char **av, int start)
{
	while (*(av + start) && ft_strncmp(*(av + start), "&&", 3)
		&& ft_strncmp(*(av + start), "||", 3))
	{
		if (!ft_strncmp(*(av + start), "(", 2))
			start = ft_skppar(av, start);
		else
			start++;
	}
	return (start);
}

static int	ft_skip_ors_if_or_and_success(char **av, int i, int size, int e_sta)
{
	if (ft_strncmp(*(av + size), "||", 3) || e_sta)
		return (size);
	while (*(av + i) && ft_strncmp(*(av + i), "&&", 3))
	{
		if (!ft_strncmp(*(av + i), "(", 2))
			i = ft_skppar(av, i);
		else
			i++;
	}
	return (i);
}

int	ft_macro_exec(char **av, char ***ev, char ***var)
{
	char	**buf;
	int		exit_status;
	int		size;
	int		i;

	i = 0;
	size = ft_to_next_logical_operator(av, i);
	if (!*(av + size))
		return (ft_execute(av, ev, var));
	while (*(av + i))
	{
		buf = ft_substrt(av, i, size - i);
		if (!buf)
			return (ft_errmsg(errno));
		exit_status = ft_execute(buf, ev, var);
		if (ft_sfree(buf) || ft_exit_toggle(STATE, 0, 0) || !*(av + size)
			|| (!ft_strncmp(*(av + size), "&&", 3) && exit_status))
			return (exit_status);
		if (ft_setio(RESET_IO) == -1)
			return (ft_errmsg(errno));
		size = ft_skip_ors_if_or_and_success(av, i, size, exit_status);
		i = size + (1 * !!*(av + size));
		size = ft_to_next_logical_operator(av, i);
	}
	return (exit_status);
}
