#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main()
{
	int pid;
	int var=66;

	pid = fork();
	if(0==pid)
	{
		printf("I am child process! pid=%d var=%d \n",pid,var);
	}	
	else
	{
		printf("I am parent process! pid=%d var=%d\n",pid,var);
	}

	return 0;
}
