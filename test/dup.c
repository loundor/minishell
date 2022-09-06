#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int ac, char **av, char **ev)
{
	int 	fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		return 1;

	if (pid2=fork() == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("cat", "cat", NULL);
	}


	if (pid1=fork() == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execlp("ls", "ls", NULL);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}