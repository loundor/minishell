/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:35:56 by stissera          #+#    #+#             */
/*   Updated: 2022/07/21 20:08:09 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*param_parse(t_cmd *str)
{
	t_shell	*shell;
	char	*ret;

	ret = NULL;
	shell = struct_passing(1, 0);
write (1, "Parssing path...\n", 18);
	(void)str;

	return (ret);
}
