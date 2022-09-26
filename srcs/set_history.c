/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:51:50 by stissera          #+#    #+#             */
/*   Updated: 2022/09/26 21:00:56 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_history(int *history)
{
	*history = open(".minishell_history", O_APPEND | O_CREAT, 0666);
	if (*history <= 0)
		printf("Can't create or read history file.\n\
			No previous history available!");
	// get next line on rl_add_history
	return (0);
}

int write_history(int *history)
{
	if (*history <= 0)
		return (0);
	// append on file the struct history was create a all line in readline.

	return (1);
}