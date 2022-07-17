/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:51 by stissera          #+#    #+#             */
/*   Updated: 2022/07/17 16:42:37 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	pwd(t_shell *shell)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->env;
	while (ft_strcmp(tmp->env_var[0], "PWD")
		|| (!ft_strcmp(tmp->env_var[0], shell->env->env_var[0] && i != 1)))
	{
		tmp = tmp->next_env;
		i = 1;
	}
	if (ft_strcmp(tmp->env_var[0], "PWD"))
		write (shell->cmd->fd, tmp->env_var[1],
			ft_strlen(tmp->env_var[1]));
	else
	{
		write (shell->cmd->fd, "NO PATH FOUND!\0", 16);
		return (1);
	}
	return (0);
}
