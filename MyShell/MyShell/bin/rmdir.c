#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
int main(int argc,char* argv[])
{
  if(argc != 2)
   printf("Usage: %s dirname",basename(argv[1])),exit(-1);
  if(rmdir(argv[1]) != 0)
   perror("rmdir"),exit(-1);
  printf("rmdir %s success!\n",argv[1]); 
  return 0;
}

