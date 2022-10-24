/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/10/04 02:09:36 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isbuiltin(char **cmd, char ***ev, char ***var)
{
	int	exit_status;

	exit_status = 0;
	if (cmd && !*cmd)
		exit_status = 0;
	else if (cmd && *cmd && !ft_strncmp(*cmd, "cd", 3))
		exit_status = ft_cd(cmd, ev, *var);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "env", 4))
		exit_status = ft_env(*ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "echo", 5))
		exit_status = ft_echo(cmd);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "pwd", 4))
		exit_status = ft_pwd(1);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "exit", 5))
		exit_status = ft_exicmd(cmd, **var + 2);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "export", 7))
		exit_status = ft_export(cmd, ev, var);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "unset", 6))
		exit_status = ft_unset(cmd, ev, var);
	else
		exit_status = -1;
	return (exit_status);
}
