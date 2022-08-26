/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:51 by stissera          #+#    #+#             */
/*   Updated: 2022/08/26 15:20:26 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd((void *)0, 0);
//	if (!pwd)
//		ft_errmsg(errno);
	ft_putendl_fd(pwd, 1); // ATTENTION TO FD!
	return (0);
}
