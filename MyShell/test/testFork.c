#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int pid;
	pid = fork();
	if(0==pid)
	{
		printf("I am child process!\n");
	}
	else
	{
		printf("I am parent proess!\n");
	}

	return 0;
}
