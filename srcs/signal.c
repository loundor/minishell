/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 10:47:21 by stissera          #+#    #+#             */
/*   Updated: 2022/09/15 08:46:19 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setsig(int type)
{
	struct sigaction sig_act_fork;
	struct sigaction sig_act_mini;

	sig_act_fork.sa_flags = SIG_IGN;
//		sig_act_fork.sa_mask = ;
//		sig_act_fork.__sigaction_handler = ;
	sig_act_mini.sa_sigaction = &ctlc_mini;
//		sig_act_mini.sa_flags = ;
//		sig_act_mini.sa_mask = ;
//		sig_act_mini.__sigaction_handler = ;
	if (type == 1)
		sigaction(SIGINT, &sig_act_fork, NULL); // ctl-c
	else
		sigaction(SIGINT, &sig_act_mini, NULL); // ctl-c
	sigaction(SIGQUIT, &sig_act_fork, NULL); // ctl-\/
	return (0);
}

void ctlc_mini(int singal, siginfo_t *info, void* context)
{
	t_shell	*shell;

	if (singal == 2)
	{
		shell = struct_passing(1, 0);
		if (shell->line != NULL)
			free_str(shell->line);
		rl_free_line_state();
		rl_newline(1, '\n');
	}
}