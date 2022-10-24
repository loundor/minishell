/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:46 by alfux             #+#    #+#             */
/*   Updated: 2022/09/16 18:21:55 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_sigmsg(int first_status, int last_status)
{
	if (WIFSIGNALED(first_status) && WTERMSIG(first_status) == SIGINT)
		write(1, "\n", 1);
	if (WIFSIGNALED(last_status) && WTERMSIG(last_status) != SIGINT)
		ft_printf("Quit: %i\n", WTERMSIG(last_status));
}
