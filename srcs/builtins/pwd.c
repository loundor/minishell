/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/29 15:11:11 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	t_env	*env;
	char	*pwd;

	env = (t_env *)struct_passing(2, 0);
	pwd = getcwd((void *)0, 0);
	if (!pwd)
		ft_errmsg(errno);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
