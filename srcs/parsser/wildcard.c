/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:51:03 by stissera          #+#    #+#             */
/*   Updated: 2022/08/26 14:51:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -----------| TO HARD TO FIND?? NOOO! |------------------ */
/*	The wildcard count and check all char until a !=		*/
/*	If the differente char is * or ?, that call the subfunc	*/
/*	and check how is the next part of the pattern. We use	*/
/*	a decressing mode that means with start end of the str	*/
/*	to search the correspondant between part of parttern	*/
/*	and str.. Use the decressing mode its maybe not the		*/
/*	good solution... After this check, if the str and patt	*/
/*	are not \0 we recall the main function (recursive)...	*/
/* -------------------------------------------------------- */

static int	part_wild_test(t_wildcard *test)
{
	int	bakp;
	int	baks;
	int	count;

	bakp = test->ps;
	baks = test->ss;
	count = baks;
	while (baks < test->se && bakp < test->pe)
	{
		if (test->str[baks] == test->pattern[bakp]
			|| test->pattern[bakp] == '?')
		{
			bakp++;
			baks++;
			continue ;
		}
		baks = ++count;
		bakp = test->ps;
	}
	if (bakp >= test->ps)
	{
		test->ss = count;
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
		while ((test->str[test->se] == test->pattern[test->pe]
				|| test->pattern[test->pe] == '?') && test->pe >= test->ps)
		{
			test->pe--;
			test->se--;
		}
		if ((test->str[++test->se] == test->pattern[++test->pe]
				|| test->pattern[++test->pe] == '?') && test->pe == test->ps)
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
