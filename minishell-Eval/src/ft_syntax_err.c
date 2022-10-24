/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:11:04 by alfux             #+#    #+#             */
/*   Updated: 2022/09/27 02:48:51 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_print_err(char *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd("minishell: syntax error near open parentheses\n", 2);
	return (1);
}

static int	ft_parentheses_err(char **tkn)
{
	int	p;

	p = 0;
	while (*tkn)
	{
		if (!ft_strncmp(*tkn, "(", 2))
			p++;
		else if (!ft_strncmp(*tkn, ")", 2))
			p--;
		tkn++;
	}
	if (p)
		return (1);
	return (0);
}

static int	ft_isfull_tkn(char *tkn)
{
	if (!ft_strncmp(tkn, "|", 2) || !ft_strncmp(tkn, "||", 3))
		return (1);
	if (!ft_strncmp(tkn, "<", 2) || !ft_strncmp(tkn, "<<", 3))
		return (1);
	if (!ft_strncmp(tkn, ">", 2) || !ft_strncmp(tkn, ">>", 3))
		return (1);
	if (!ft_strncmp(tkn, "&&", 3))
		return (1);
	if (!ft_strncmp(tkn, "(", 2) || !ft_strncmp(tkn, ")", 2))
		return (2);
	return (0);
}

static int	ft_err_near(char **tkn)
{
	int	type;

	type = ft_isfull_tkn(*tkn);
	if (!type && !ft_strncmp(*(tkn - 1), ")", 2))
		return (1);
	else if (type == 1)
	{
		if (ft_isfull_tkn(*(tkn - 1)) == 1 || !ft_strncmp(*(tkn - 1), "(", 2))
			return (1);
		if (!*(tkn + 1))
			return (1);
	}
	else if (type == 2)
	{
		if (!ft_strncmp(*tkn, "(", 2) && ft_strncmp(*(tkn - 1), "(", 2)
			&& ft_isfull_tkn(*(tkn - 1)) != 1)
			return (1);
		if (!ft_strncmp(*tkn, ")", 2) && ft_strncmp(*(tkn - 1), ")", 2)
			&& ft_isfull_tkn(*(tkn - 1)))
			return (1);
	}
	return (0);
}

int	ft_syntax_err(char **tkn)
{
	if (!*tkn)
		return (0);
	if (ft_isfull_tkn(*tkn) == 1)
		return (ft_print_err(*tkn));
	if (ft_parentheses_err(tkn))
		return (ft_print_err((char *)0));
	tkn++;
	while (*tkn)
	{
		if (ft_err_near(tkn))
			return (ft_print_err(*tkn));
		tkn++;
	}
	return (0);
}
