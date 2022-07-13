# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <sys/wait.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>


int main(int argc, char **argv, char **env)
{

	printf("%s\n", env[0]);
	return (0);
}
