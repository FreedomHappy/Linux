#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> //getpwuid
#include <pwd.h> //getpwuid,passwd
#include <unistd.h> //pipe,dup2
//指令行提示
void lsh_prompt()
{
    const int max_name_len = 256;
    const int max_path_len = 1024;
    
    char prompt[max_name_len+max_path_len+100];
    struct passwd *pwd;
    char hostname[max_name_len];
    char path[max_path_len];
    int length;		
    pwd = getpwuid(getuid());
    getcwd(path,max_path_len);
    if(gethostname(hostname,max_name_len)==0)
        sprintf(prompt,"[MyShell]%s@%s:",pwd->pw_name,hostname);
    else
        sprintf(prompt,"[Myshell]%s@unknown:",pwd->pw_name);
    length = strlen(prompt);
    if(strlen(path) < strlen(pwd->pw_dir) || 
            strncmp(path,pwd->pw_dir,strlen(pwd->pw_dir))!=0)
        sprintf(prompt+length,"%s",path);
    else
        sprintf(prompt+length,"~%s",path+strlen(pwd->pw_dir));
    length = strlen(prompt);
    if(geteuid()==0)
        sprintf(prompt+length,"# ");
    else
        sprintf(prompt+length,"$ ");
    printf("%s",prompt);
    return;
}

/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}


//读取指令
#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char));
  int c;

  if (!buffer) {
    fprintf(stderr,"lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;
	
    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer,bufsize);
      if (!buffer) {
        fprintf(stderr,"lsh: allocation error\n");
    	exit(EXIT_FAILURE);
      }
    }	
  }
}

//解析指令
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;
    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
// function for finding pipe 
int findPipe(char *args1[],char *args2[],char ** args)
{ 
  //printf("start find pipe! %s\n",args[0]);
  int i=0;
  while(1)
  {
    if(args[i]==NULL)
    { 
     // printf("not find pipe!\n");
      return 0; 
    }	  
    if(strcmp(args[i],"|")==0)
    { 
      break;
    }
   
    i++;
  }
  int j=0;
  while(1)
  {
    if(j>=i)
    {break;}
    args1[j]=args[j];
    j++;
  }
  args1[j]=NULL;
  
  int length = 0;
  // 计算args长度
  while(args[length]!=NULL)
  {
    length++;
  }
  
 

  for(int k=i+1,j=0; k<length; k++)
  {
    args2[j]=args[k];
    j++;
  }
  args2[j]=NULL;
  return 1;
}
int lsh_launch(char **args)
{ //printf("launch");
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

#define PATH "./bin/"
int lsh_PATH_exec(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    char *path = malloc(strlen(PATH)+strlen(args[0])+1);
    if (path==NULL){exit(EXIT_FAILURE);}
    strcpy(path,PATH);
    strcat(path,args[0]);
    if (execv(path, args) == -1) {
       //perror("lsh");
       exit(EXIT_FAILURE); 
    }
    exit(EXIT_SUCCESS);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  //正常退出判断
  if(WIFEXITED(status)){
    //printf("child exit with %d\n", WEXITSTATUS(status));
    if(WEXITSTATUS(status))
    {
      return 0;
    }
    return 1;
  }

  //因为某种信号中断获取状态
  if(WIFSIGNALED(status)){
    //printf("child killed by %d\n", WTERMSIG(status));
    return 0;
  }
  return 0;
}
/*
int lsh_execPipe(char **args1,char **args2)
{
  pid_t pid;
  int fd[2];
  pipe(fd);
  pid=fork();
  if(0==pid)//execute next command in child process
  {  
	close(fd[0]);
	dup2(fd[1],1);//redirect standard output to pipe(write)
	//close(fd[1]);
        printf("start pipeChild!\n");
	if(0!=execvp(args1[0],args1))
	{
	  perror("No such command!");
	  //exit(EXIT_FAILURE);
	}	
	exit(EXIT_SUCCESS);
  } 
  else//execute current command in current process 
  {     
	wait(NULL);
       	close(fd[1]);
	dup2(fd[0],0);//redirect standard input to pipe(read)
	//close(fd[0]);
        printf("start pipeParent!\n");
	if(0!=execvp(args2[0],args2))
		perror("No such command!");

	return 1;
  }
}
*/
void lsh_execPipe(char ** argv1,char ** argv2)
{
    pid_t pid = fork();
    if(pid == -1)                                                                                                                       
    {                                                                                                                           
        perror("fork()");
    }
    else if(pid == 0)
    {
        //child,创建一个管道
        int fd[2];
        int ret = pipe(fd);

        if(fork() == 0 )
        {
            //子进程创建一个子进程，用于执行管道之前的命令
            close(fd[0]); //孙子进程关闭掉读端
            dup2(fd[1],1);  //将标准输出作为管道的标准输入
            execvp(argv1[0],argv1);
        }
        wait(NULL);
        close(fd[1]); //子进程关闭掉写端

        dup2(fd[0],0);   //将标准输入重定向至管道的读端
        execvp(argv2[0],argv2);
        //execvp失败会执行下面的语句
        perror("execvp()");
        exit(0);    
    }
    else
    {
        //parent
        wait(NULL);                                                                                                                     
    }

}

int lsh_execute(char ** args)

{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
  //执行内建指令
  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
 
  //管道命令
  char *args1[10],*args2[10];
  if(findPipe(args1,args2,args))
  {
     //printf("find pipe\n");
     lsh_execPipe(args1,args2);
     return 1;
  }
  
  //执行外部环境变量
  if(!lsh_PATH_exec(args))
  {  //printf("no find\n ");
  	return lsh_launch(args);
  }
  return 1;
}
void lsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do{
	lsh_prompt();
	line = lsh_read_line();
	args = lsh_split_line(line);
	status = lsh_execute(args);

	free(line);
	free(args);
	}while(status);
}

int main(int argc, char **argv)
{
	// Load config files, if any.
	
	// Run command loop.
	lsh_loop();

	// Perform any  shutdown/cleanup.
	
	return EXIT_SUCCESS;
}
