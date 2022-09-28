/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:51:50 by stissera          #+#    #+#             */
/*   Updated: 2022/09/28 20:27:13 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	free_history(t_history *hist)
{
	if (hist->next)
		free_history(hist->next);
	free(hist->line);
	free(hist);
	return (0);
}

static char	*ft_charrpl(char *str, int search, int rmpl)
{
	int	i;

	i = 0;
	if (!str || *str == 0)
		return (str);
	while (str[i] != 0)
	{
		if (str[i] == search)
			str[i] = rmpl;
		i++;
	}
	return (str);
}

void	add_list_history(char *line, t_shell *shell)
{
	t_history	*last;
	t_history	*new;

	last = NULL;
	new = (t_history *)malloc(sizeof(t_history) * 1);
	if (!new)
			exit (ft_exit(errno, 1));
	new->line = ft_strdup(line);
	new->next = NULL;
	if (shell->h_list == NULL)
		shell->h_list = new;
	else
	{
		last = shell->h_list;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	return ;
}

int	ft_set_history(t_shell *shell)
{
	char	*line;

	line = NULL;
	shell->history = open(".minishell_history", O_RDONLY | O_CREAT, 0666);
	if (shell->history <= 0)
		printf("\001\033[1;31m\002Can't create or read history file.\n\
No previous history available!\n\001\033[0m");
	if (shell->history)
	{
		line = get_next_line(shell->history);
		while (line != NULL)
		{
			line = ft_charrpl(line, '\n', 0);
			add_history(line);
			line = get_next_line(shell->history) + free_str(line);
		}
		close (shell->history);
	}
	return (0 + free_str(line));
}

int ft_write_history(t_shell *shell)
{
	t_history	*hist;

	hist = shell->h_list;
	if (shell->history <= 0 || shell->h_list == NULL)
		return (0);
	shell->history = open(".minishell_history", O_RDWR
		| O_APPEND | O_CREAT, 0666);
	if (shell->history <= 0)
		return (0 * printf("\001\033[1;31m\002\
Writing probleme on history file!\n\001\033[0m")
			+ free_history(shell->h_list));
	while (hist->next != NULL)
	{
		write(shell->history, "\n", 1);
		write(shell->history, hist->line, ft_strlen(hist->line));
		hist = hist->next;
	}
	write(shell->history, "\n", 1);
	write(shell->history, hist->line, ft_strlen(hist->line));
	close(shell->history);
	free_history(shell->h_list);
	return (0);
}
