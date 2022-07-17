/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 10:47:21 by stissera          #+#    #+#             */
/*   Updated: 2022/07/17 16:57:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_signal(int signo, siginfo_t *info, void *context)
{
	context = NULL; // Look about what is context maybe old act??!!
	if (info->si_signo == 2)
	{
		
	}
	return (0);
}

int	prep_signal(t_shell *shell)
{
	shell->signal_act.sa_sigaction = &get_signal;
	sigaction(SIGINT,shell, NULL); // ctl-c
	sigaction(SIGQUIT, shell, NULL); // ctl-\/
	return (0);
}
