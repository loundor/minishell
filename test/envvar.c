# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
# include <errno.h>


typedef struct s_shell
{
	char				*line;
	short unsigned int	*return_err;
	struct s_env		*env;
	struct s_cmd		*cmd;
	struct s_tree		*tree;
	struct s_builtins	*builtin;
	struct sigaction	signal_act;
}	t_shell;

typedef struct s_env
{
	struct s_env	*prev_env;
	char			**env_var;
	struct s_env	*next_env;
}	t_env;