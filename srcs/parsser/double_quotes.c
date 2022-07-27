/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:23:10 by stissera          #+#    #+#             */
/*   Updated: 2022/07/27 16:24:12 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ---------------|					 |------------------- */
/*															*/
/* -------------------------------------------------------- */
char	*take_double_quote(char *param)
{
	size_t	count;

	count = 0;
	param++;
	if (param == NULL)
		return (NULL);	// For test but NEED sent to HEREDOC!
	while (param[count] != '"' || param[count] != '\0')
		count++;
	if (*param )
		return (NULL);
	return (param);
}
