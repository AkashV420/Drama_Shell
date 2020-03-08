#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];



int drama_Check(char **args)
{
    int original_stdout = dup(1);
    int original_stdin = dup(0);
    int argc = 0;
    char *str = checkInputRedirection(args);
    if(str)
    {   
        // printf("Input redirect %s\n",str);
        int fd;
        // open the file to replace stdout
        fd = open(str, O_RDONLY);

        if(fd == -1) {
          perror("Failed to open file");
        }
        // close(0);
        // use dup2() to duplicate the fd
        if(dup2(fd, 0) != 0)  // 1 refers to stdout
          perror("dup2 fail");
        // close the original fd
        close(fd);

    }
    str = checkOutputRedirection(args);
    if(str)
    {   
        // printf("this is the file   %s\n", str);
        int fd;
        // open the file to replace stdout
        fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // printf("mehengi randi\n");
        if(fd == -1) {
          perror("Failed to open file");
        }
        // printf("sasti randi here\n");
        // close(1);
        // use dup2() to duplicate the fd
        if(dup2(fd, 1) != 1) { // 1 refers to stdout
          perror("dup2 fail");
      	}
      	// printf("sex\n");
        // close the original fd
        // close(fd);
    }
    str = checkAppendRedirection(args);
    if(str)
    {  
        int fd;
        // open the file to replace stdout
        fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);

        if(fd == -1) {
          perror("Failed to open file");
        }
        // close(1);
        // use dup2() to duplicate the fd
        if(dup2(fd, 1) != 1)  // 1 refers to stdout
          perror("dup2 fail");
        // close the original fd
        // close(fd);
    }
    
    for(argc = 0; args[argc]!=NULL; argc++);
    // printf("inside drama check %d\n", argc);

    if(strcmp(args[0], "jobs")==0)
    {
    	drama_jobs(args);
    	
    }
    if(strcmp(args[0], "kjob")==0)
    {
    	drama_kjob(args);
    	
    }
    if(strcmp(args[0], "fg")==0)
    {
    	drama_fg(args);
    	
    }
    if(strcmp(args[0], "bg")==0)
    {
    	drama_bg(args);
    	
    }
    if(strcmp(args[0], "setenv")==0)
    {
    	drama_setenv(args);
    	
    }
    if(strcmp(args[0], "unsetenv")==0)
    {
    	drama_unsetenv(args);
    	
    }
    if(strcmp(args[0], "overkill")==0)
    {
    	drama_overkill(args);
    }
    //Restore the original I\O field
    // fflush(stdin);
    
    int status = drama_Execute(argc,args);

    fflush(stdout);
    dup2(original_stdout,1);
    dup2(original_stdin,0);
    close(original_stdout);
    close(original_stdin);
    
    checkBackgroud();
    return status;
}