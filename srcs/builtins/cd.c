/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:42 by stissera          #+#    #+#             */
/*   Updated: 2022/08/27 18:46:43 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_shell *shell)
{
	if (chdir(shell->cmd->param))
		return (ft_errmsg(errno));
	set_env_splited(shell->env, shell->cmd->param, "PWD");
	return (0);
}