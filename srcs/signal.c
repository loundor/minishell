/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 10:47:21 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 20:32:03 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctlc_mini(int singal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (singal == 2)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	setsig(int type)
{
	struct sigaction	sig_act_fork;
	struct sigaction	sig_act_mini;

	sig_act_fork.sa_handler = SIG_IGN;
	sig_act_fork.sa_flags = 0;
	sig_act_mini.sa_sigaction = &ctlc_mini;
	sig_act_mini.sa_flags = SIGQUIT;
	if (type == 1)
	{
		sigaction(SIGINT, &sig_act_fork, NULL);
		sigaction(SIGQUIT, &sig_act_fork, NULL);
		return (0);
	}
	else
	{
		sigaction(SIGINT, &sig_act_mini, NULL);
		sigaction(SIGQUIT, &sig_act_mini, NULL);
		return (0);
	}
	return (1);
}
