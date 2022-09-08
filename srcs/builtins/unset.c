/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:36:53 by stissera          #+#    #+#             */
/*   Updated: 2022/09/08 21:17:08 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(char **par)
{
	char	*param;
	t_shell	*shell;

	param = par[1];
	shell = struct_passing(1, 0);
	rem_env(shell->env, param);
	return (0);
}
