/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istokn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:44:26 by alfux             #+#    #+#             */
/*   Updated: 2022/09/27 02:32:35 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_istokn(char *c)
{
	if (*c == '|' || *c == '<' || *c == '>' || (*c == '&' && *(c + 1) == '&'))
		return (1);
	if (*c == '(' || *c == ')')
		return (2);
	return (0);
}