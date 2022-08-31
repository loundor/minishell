/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 17:44:46 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_errmsg_a(int errn)
{
	if (errn == -1)
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
	else if (errn == -2)
		ft_putstr_fd("Error: Unclosed double quotes\n", 2);
	else if (errn == -3)
		ft_putstr_fd("Error: Couldn't find USER in environnement\n", 2);
	else if (errn == -4)
		ft_putstr_fd("Error: Command not found\n", 2);
	return (errn);
}

int	ft_errmsg(int errn)
{
	errno = errn;
	if (errn == EACCES)
		ft_putstr_fd("Error: Permission denied\n", 2);
	else if (errn == EFAULT)
		ft_putstr_fd("Error: Path is outside of allocated address space\n", 2);
	else if (errn == EIO)
		ft_putstr_fd("Error: I/O error occured while r/w file system\n", 2);
	else if (errn == ELOOP)
		ft_putstr_fd("Error: Too many symbolic links (looping?)\n", 2);
	else if (errn == ENAMETOOLONG)
		ft_putstr_fd("Error: Path/name is too long", 2);
	else if (errn == ENOENT)
		ft_putstr_fd("Error: Component of pathname does not exist\n", 2);
	else if (errn == ENOTDIR)
		ft_putstr_fd("Error: Not a directory\n", 2);
	else if (errn == ENOMEM)
		ft_putstr_fd("Error: Insufficient memory available\n", 2);
	else if (errn == EINVAL)
		ft_putstr_fd("Error: Invalid argument value\n", 2);
	else if (errn == ERANGE)
		ft_putstr_fd("Error: Argument(s) out of range\n", 2);
	else
		return (ft_errmsg_a(errn));
	return (errn);
}
