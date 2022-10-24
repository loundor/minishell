/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 01:32:25 by alfux             #+#    #+#             */
/*   Updated: 2022/10/03 17:16:17 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_pwd(int err)
{
	char	*pwd;

	pwd = ft_newpwd();
	if (!pwd)
	{
		if (err)
			ft_errmsg(errno);
		return (1);
	}
	ft_printf("%s\n", pwd);
	(void)ft_free(pwd);
	return (0);
}
