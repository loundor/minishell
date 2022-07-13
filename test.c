# include "./libft.h"
//# include "../lib/libft/gnl/gnl.h"
# include <unistd.h>
# include <stdio.h>
//# include <stdlib.h>
//# include <fcntl.h>
//# include <signal.h>
//# include <curses.h>
//# include <sys/wait.h>
//# include <term.h>
//# include <readline/history.h>
//# include <readline/readline.h>

typedef enum e_typeerror
{
	ALLRIGHT,
	ENV,
	MALLOCERR,
	WELCOME_ERR,
	NO_ENV
}	t_error;

typedef struct s_env
{
	struct s_env	*prev_env;
	char			**env_var;
	struct s_env	*next_env;
}	t_env;

typedef struct s_cmd
{
	char			*command;
	char			*param;
	char			*option;
	struct s_redi	*redirection;
	struct s_pipe	*pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	struct s_env	*env;
	struct s_cmd	cmd;
}	t_shell;

t_env	*do_env(char **env)
{
	t_env	*tenv;
	t_env	*ret;
	t_env	*parsse;

	if (*env)
	{
		tenv = malloc(sizeof(t_env));
		if (!tenv)
			return (NULL);
		tenv->env_var = ft_split(*env, '=');
		ret = tenv;
		env++;
	}
	else
		return (NULL);
	while (*env)
	{
		parsse = 0;
		parsse = malloc(sizeof(t_env));
		if (!parsse)
			return (NULL);
		parsse->prev_env = tenv;
		parsse->env_var = ft_split(*env, '=');
		tenv->next_env = parsse;
		tenv = tenv->next_env;
		env++;
	}
	tenv->next_env = ret;
	ret->prev_env = tenv;
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = do_env(env);
	if (!shell.env)
		return(1);

while (shell.env->env_var[0])
{
	printf("%s=%s\n", shell.env->env_var[0],shell.env->env_var[1]);
	shell.env = shell.env->next_env;
}
	return (0);
}
