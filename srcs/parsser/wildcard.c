/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:51:03 by stissera          #+#    #+#             */
/*   Updated: 2022/08/23 22:56:27 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	part_wild_test(t_wildcard *test)
{
	int	bakp;
	int	baks;
	int	count;

	bakp = test->pe - 1;
	baks = ft_strlen(test->str) - 1;
	count = baks;
	while (bakp > test->ps)
	{
		if (test->str[baks] == test->pattern[bakp])
		{
			bakp--;
			baks--;
			continue ;
		}
		baks = --count;
		bakp = test->pe - 1;
	}
	if (bakp == test->ps)
	{
		test->ss = baks;
		return (1);
	}
	return (0);
}

static int	parse_wildcard(t_wildcard *test)
{
	test->pe = test->ps;
	while (test->pattern[test->pe] != 0 && test->pattern[test->pe] != 42)
		test->pe++;
	if (test->pattern[test->pe] == 0)
	{
		while (test->str[test->se] == test->pattern[test->pe]
			&& test->pe >= test->ps)
		{
			test->pe--;
			test->se--;
		}
		if (test->str[++test->se] == test->pattern[++test->pe]
			&& test->pe == test->ps)
			return (1);
		return (0);
	}
	if (part_wild_test(test))
	{
		if (test->se != test->ss)
			return (starcmp(test));
		return (0);
	}
	return (0);
}

int	starcmp(t_wildcard	*test)
{
	test->se = ft_strlen(test->str);
	while (test->pattern[test->ps] == test->str[test->ss]
		|| test->pattern[test->ps] == '?'
		&& (test->pattern[test->ps] != 0 && test->str[test->ss] != 0))
	{
		test->ss++;
		test->ps++;
	}
	if (test->pattern[test->ps] == 0 && test->str[test->ss] == 0)
		return (1);
	if (test->pattern[test->ps] == '*')
	{
		while (test->pattern[test->ps] == '*')
			test->ps++;
		if (test->pattern[test->ps] == 0)
			return (1);
		return (parse_wildcard(test));
	}
	return (0);
}
