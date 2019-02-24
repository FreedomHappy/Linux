#include<unistd.h>
#include<stdio.h>

int main()
{
	int fd[2];
	pipe(fd);
	pid=fork();

	if(0==pid)//execute next command in child process
	{
		dup2(fd[0],0);//redirect standard input to pipe(read)
		close(fd[0]);
		close(fd[1]);
		
		if(0!=execvp(cmd0[0],cmd0))
		{
			printf("No such command! \n");
		}
		exit(EXIT_SUCCESS);
	}
	else//execute current command in current process
	{
		dup2(fd[1],1);//redirect standard output to pipe(write)
		close(fd[0]);
		close(fd[1]);

		if(0!=execvp(cmd1[0],cmd1))
		{
			printf("No such commadn! \n");
		}
		exit(EXIT_SUCCESS);
	}
}
