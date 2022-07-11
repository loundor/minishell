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

//	int i = -1;
	printf("%d\n", argc);
	printf("%d\n", rl_eof_char);
//	while(argv[++i])
//		printf("ARGV: %s\n", argv[i]);
	//i = -1;
	//while(env[++i])
	//	puts(env[i]);
char * inpt = readline("Enter text: ");
printf("%s\n", inpt);
	return (0);
}
