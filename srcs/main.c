/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:07:29 by stissera          #+#    #+#             */
/*   Updated: 2022/07/13 11:58:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = do_env(env);
	if (!shell.env)
		exit(ft_error(ENV));
	
	if (argc == 1)
		(void)argv;
	else
		create_command(**argv, shell);

	if (welcome() != 0)
		exit (ft_error(WELCOME_ERR));

	if (!prompt())
		return (0);
}

t_env	*do_env(char **env)
{
	t_env	*tenv;
	t_env	*ret;
	t_env	*parsse;

	if (**env)
	{
		tenv = malloc(sizeof(t_env));
		if (!tab)
			exit(ft_error(MALLOCERR));
		tenv->env_var = ft_split(**env, '=');
		ret = tenv;
	}
	else
		exit(ft_error(NO_ENV));
	while (++*env)
	{
		parsse = NULL;
		parsse = malloc(sizeof(t_env));
		if (!parsse)
			exit(ft_free_lvl(1));
		parsse->prev_env = tenv;
		parsse->env_var = ft_split(**env, '=');
		tenv->next_env = parsse;
		tenv = tenv->next_env;
	}
	parsse->next_env = tenv;
	tenv->prev_env = parsse;
	return (tenv);
}
