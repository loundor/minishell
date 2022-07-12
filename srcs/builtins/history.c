/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:08:03 by stissera          #+#    #+#             */
/*   Updated: 2022/07/12 10:43:27 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	w_history(char **history)
{
	int	history_fd;

	if (!check_auth("./", FILE_HISTORY))
		return (msg_err(ACCESS_ERR));
	history_fd = open("./.minishell_history", O_CREAT | O_RDWR | O_APPEND);
	if (history_fd < 0)
		return (history_fd);

	return (1);
}
