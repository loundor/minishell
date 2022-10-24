/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_macros.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:06:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/27 01:35:47 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FLAGS_MACROS_H
# define FLAGS_MACROS_H

# define HISTORY ".minishell_history"
//--------------------------------ft_setio-flags--------------------------------
enum
{
	SAVE_IO,
	RESET_IO,
	CLOSE_IO,
	RESET_IN,
	RESET_OUT
};
//------------------------------------------------------------------------------
//--------------------------------ft_sighdl-flags-------------------------------
enum
{
	HDL_PROMPT_SIGINT = 1,
	HDL_IGNORE_SIGINT = 2,
	HDL_IGNORE_SIGQUIT = 4,
	HDL_REINIT_SIGINT = 8,
	HDL_REINIT_SIGQUIT = 16
};
//------------------------------------------------------------------------------
//--------------------------------ft_exit_toggle-flags--------------------------
enum
{
	STATE,
	SAVE_HISTORY,
	NO_SAVE_HISTORY
};
//------------------------------------------------------------------------------
# define SIGMSG_1 "Hangup: 1"
# define SIGMSG_3 "Quit: 3"
# define SIGMSG_4 "Illegal instruction: 4"
# define SIGMSG_5 "Trace/BPT trap: 5"
# define SIGMSG_6 "Abort trap: 6"
# define SIGMSG_7 "EMT trap: 7"
# define SIGMSG_8 "Floating point exception: 8"
# define SIGMSG_9 "Killed: 9"
# define SIGMSG_10 "Bus error: 10"
# define SIGMSG_11 "Segmentation fault: 11"
# define SIGMSG_12 "Bad system call: 12"
# define SIGMSG_14 "Alarm clock: 14"
# define SIGMSG_15 "Terminated: 15"
# define SIGMSG_24 "Cputime limit exceeded: 24"
# define SIGMSG_25 "Filesize limit exceeded: 25"
# define SIGMSG_26 "Virtual timer expired: 26"
# define SIGMSG_27 "Profiling timer expired: 27"
# define SIGMSG_30 "User defined signal 1: 30"
# define SIGMSG_31 "User defined signal 2: 31"
#endif
