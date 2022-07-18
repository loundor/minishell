/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 10:47:21 by stissera          #+#    #+#             */
/*   Updated: 2022/07/18 12:06:41 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_signal(int signo, siginfo_t *info, void *context)
{
	context = NULL; // Look about what is context maybe old act??!!

	(void)info;

	if (signo == 2 || signo == 6)
	{
		rl_free_line_state();
		rl_newline(1, '\n');
	}	
	if (signo == 3)
	{
		write(1, "exit\n", 5);
	}
}

int	prep_signal(t_shell *shell)
{
	shell->signal_act.sa_sigaction = &get_signal;
	sigaction(SIGINT, &shell->signal_act, NULL); // ctl-c
	sigaction(SIGABRT, &shell->signal_act, NULL); // ctl-\/

	return (0);
}
