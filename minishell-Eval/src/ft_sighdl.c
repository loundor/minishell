/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:35:38 by alfux             #+#    #+#             */
/*   Updated: 2022/09/16 16:45:03 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_ignore_sigact(int sig)
{
	struct sigaction	sigact;

	sigact.__sigaction_u.__sa_handler = SIG_IGN;
	(void)sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	return (sigaction(sig, &sigact, (struct sigaction *)0));
}

static int	ft_newprmt_sigint(void)
{
	struct sigaction	sigint;

	sigint.__sigaction_u.__sa_handler = &ft_newpmt;
	(void)sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
	return (sigaction(SIGINT, &sigint, (struct sigaction *)0));
}

static int	ft_reinit_sigact(int sig)
{
	struct sigaction	reinit;

	reinit.__sigaction_u.__sa_handler = SIG_DFL;
	(void)sigemptyset(&reinit.sa_mask);
	reinit.sa_flags = 0;
	return (sigaction(sig, &reinit, (struct sigaction *)0));
}

int	ft_sighdl(int flag)
{
	int	exit_status;

	exit_status = 0;
	if (flag & HDL_REINIT_SIGINT)
		exit_status = exit_status | ft_reinit_sigact(SIGINT);
	if (flag & HDL_REINIT_SIGQUIT)
		exit_status = exit_status | ft_reinit_sigact(SIGQUIT);
	if (flag & HDL_PROMPT_SIGINT)
		exit_status = exit_status | ft_newprmt_sigint();
	if (flag & HDL_IGNORE_SIGINT)
		exit_status = exit_status | ft_ignore_sigact(SIGINT);
	if (flag & HDL_IGNORE_SIGQUIT)
		exit_status = exit_status | ft_ignore_sigact(SIGQUIT);
	if (!flag && !(flag >> 1) && !(flag >> 2) && !(flag >> 3) && !(flag >> 4))
		exit_status = -1 + (0 * ft_errno(EINVAL));
	return (exit_status);
}
