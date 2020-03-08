#include "library.h"
#include "functions.h"

const int MAX_PIPE = 20;

int checkPipe(char *cmd)
{
    int n=0;
    int i;
    n = strlen(cmd);
    i=0;
    while(i < n)
    {
        if(cmd[i]=='|')
        {
            return i;
        }
     i = i + 1;
    }
    return -1;
}

// function for getting pipe
char ** parsePipe(char* cmd)
{
    int count = 0;
    char *sep = "|";
    char *str = strdup(cmd);
    char **pipelets = malloc(MAX_PIPE * sizeof(char *));
    pipelets[count++] = strtok(str,sep);
    int par = 0;
    while(pipelets[count-1])
    {
        pipelets[count++] = strtok(NULL,sep);
    }
    pipelets[count++] = NULL;
    return pipelets;
}

int pipeExec(char *cmd, char **args)
{
    int i, fd;
    int flag;
    int fildes[2]; 
    int pipe_count;
    int original_stdin;
    int original_stdout;
    //If no pipe go to execCmd.c functions
    //fprintf(stderr, "macchar ke jhaant %s\n", cmd);
    if(checkPipe(cmd)==-1)
        return drama_Check(args); //return //execCmd(cmd);

    char **pipelets = parsePipe(cmd);
    pipe_count = argCount(pipelets);
    // for(int i=0;i<pipe_count;i++)
        // pipelets[i]=parseCommand(pipelets[i]);

    original_stdout = dup(1);
    original_stdin = dup(0);
    
    //Cross pipe joining var
    fd = dup(0);

    i=0;
    while(i < pipe_count)
    {
        //fprintf(stderr, "gand ka pila %s running\n", pipelets[i]);
        if(dup2(fd,0) < 0)
        {
            perror("drama_Shell::dup2 failed");
        }
        close(fd);
        
        if(i == pipe_count-1)
        {
            if(dup2(original_stdout,1) < 0)
            {
                perror("drama_Shell::dup2 failed");
            }
            close(original_stdout);
        }
        else
        {
            pipe(fildes);
            fd=fildes[0];
            
            if(dup2(fildes[1],1) < 0)
            {
                perror("drama_Shell::dup2 failed");
            }
            
            close(fildes[1]);
            // close(fildes[0]);
        }
        //fprintf(stderr, "majdoor lund %s majdoori kr raha h\n", pipelets[i]);
        char **chote_args = splitTokens(pipelets[i]);
        flag = drama_Check(chote_args);
    
      i = i+1;
    }


    //Restore the original I\O field
    // fflush(stdout);
    dup2(original_stdout,1);
    dup2(original_stdin,0);
    close(original_stdout);
    close(original_stdin);
    
    if(i != pipe_count)
    {
        printf("Command %d not executed properly\n",i+1);
        return 1;
    }
    return 1;
}
