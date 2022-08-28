/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:42 by stissera          #+#    #+#             */
/*   Updated: 2022/08/28 10:27:48 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_shell *shell)
{
	if (chdir(shell->cmd->param))
		return (ft_errmsg(errno));
	set_env(shell->env, shell->cmd->param, "PWD");
	return (0);
}