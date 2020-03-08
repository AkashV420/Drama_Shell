#include "library.h"
#include "functions.h"

char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];
int gaanja_pid;
int gaanjaGun = 0;

void gaanjaHandler(int signum)
{
    gaanjaGun = 1;
    kill(gaanja_pid, SIGTSTP);
    return;
}

struct Process
{
  int  pid;
  int status; //status 1 shows running, 0 shows stopped
  char cmd[1024];
};

struct Process backgroundProcess[1024];

int processPointer=0;

int drama_Proc(char **args)
{
    
    int status=1, background = 0;
    
    int argc = argCount(args);

    int check = 0;
    
    pid_t pid,wpid;
    //background is defined when last argument is &
    
    if(!strcmp(args[argc-1],"&"))
        background = 1;
    
    pid = fork();
    if(pid < 0)
    {
        //give fork error
        perror("drama_Shell: fork error..");
        _exit(1);
    }
    else if(!pid)
    {
        //child process should call execvp
        if(background)
        {
            args[argc - 1] = NULL; ////////////
            setpgid(0,0);   
        }
        
         check = execvp(args[0],args);
        
        if(check < 0)
        {
            //perror("drama_Shell:");
            //If not killed multiple copies of shell would open
            _exit(1);
        }
    }
    else if(!background)
    {
        //parent Process for forground Process
        //Set global foreground process pid
        gaanja_pid = pid;
        signal(SIGTSTP, gaanjaHandler);
        waitpid(pid,NULL,WUNTRACED); /////////////////////////updated!!
        if(gaanjaGun == 1) 
        {
            backgroundProcess[processPointer].status = 1;
            backgroundProcess[processPointer].pid = pid;
            strcpy(backgroundProcess[processPointer].cmd,args[0]);
            processPointer = processPointer + 1;
            printf("[+] %s [%d]\n",args[0],pid);
            gaanjaGun = 0;
        }

           
    }
    else
    {
        kill(pid,SIGCONT);
        //parent process for background Process
        backgroundProcess[processPointer].status = 1;
        backgroundProcess[processPointer].pid = pid;
        strcpy(backgroundProcess[processPointer].cmd,args[0]);
        processPointer = processPointer + 1;
        printf("[+] %s [%d]\n",args[0],pid);
    }
    return status;
        }

int checkBackgroud()
{   
    int status;
    int wpid;
    int bg=0;
    int i=0;
    while(i < processPointer)
    {
        if(backgroundProcess[i].pid!=0 && bg == 0)
        {
            wpid = waitpid(backgroundProcess[i].pid,&status,WNOHANG);
            if(wpid==backgroundProcess[i].pid && bg == 0)
            {
                printf("[drama_Shell: %s with pid %d exited with status %d]\n",backgroundProcess[i].cmd,wpid,WIFEXITED(status));
                backgroundProcess[i].pid=0;
            }
        }
        i = i + 1;  
    }
    return 0;
}


int drama_fg(char **args)
{  
    int count=0;
    int i, pindex=0;
    int status;
    int check;
    int argc = argCount(args);
    if(argc!=2)
    {
        fprintf(stderr,"%s\n","drama_Shell:Enter as fg <process index from jobs>");
        return -1;
    }
  
    pindex = atoi(args[1]);
   
    i=0;
    while(i < processPointer)
    {
        if(backgroundProcess[i].pid)
            count = count + 1;
        
        if(count == pindex)
        {
            
            check = kill(backgroundProcess[i].pid,SIGCONT);
            tcsetpgrp(0, backgroundProcess[i].pid);
            signal(SIGTTOU, SIG_IGN);
            pid_t wpid = waitpid(backgroundProcess[i].pid,&status,WUNTRACED);
            tcsetpgrp(0, getpid());

            signal(SIGTTOU, SIG_DFL);            
            //Remove from background process array
            if(!check)
                backgroundProcess[i].pid=0;
            return check;
        }
        i= i + 1;
    }
    if(i==processPointer)
    {
        fprintf(stderr,"%s\n","drama_Shell:Not valid process index use jobs for index\n");
        return -1;
    }
    return 0;
}

int drama_bg(char **args)
{   


     int i;
     int check = 0;
     int count=0;
    int argc = argCount(args);
    if(argc!=2)
    {
        fprintf(stderr,"%s\n","drama_Shell:Enter as bg <process index from jobs>");
        return -1;
    }
     //kill(backgroundProcess[i].pid,SIGCONT);
    
    i=0;
    int pindex = atoi(args[1]);
    
    while(i < processPointer)
    {
        
        if(backgroundProcess[i].pid)
            count = count + 1;
        
        if(count == pindex)
        {
            check = kill(backgroundProcess[i].pid,SIGCONT);
            backgroundProcess[i].status = 1;
            return check;
        }
     i = i + 1;
    }

    if(i==processPointer)
    {
        fprintf(stderr,"%s\n","drama_Shell:Not valid process index use jobs for index\n");
        return -1;
    }
    return 0;
}

int drama_jobs(char **args)
{  
    int check = 0,i;
    
    int count=0;
    
    int argc = argCount(args);
    
    if(argc!=1)
    {
        fprintf(stderr,"%s\n","drama_Shell:Enter as jobs\n");
        return -1;
    }
     
    i=0;                                   
    while(i < processPointer)
    {
        if(backgroundProcess[i].pid)
        {
            count = count + 1;
            
            if(backgroundProcess[i].status)
                printf("\t[%d]\trunning\t%s\t[%d]\n",count,backgroundProcess[i].cmd,backgroundProcess[i].pid);
            else    
                printf("\t[%d]\tstopped\t%s\t[%d]\n",count,backgroundProcess[i].cmd,backgroundProcess[i].pid);
        }
        i = i + 1;
    }
    return 0;
}
int drama_kjob(char **args)
{   
    int check = 0; 
    int argc = argCount(args);
    int count=0;
    int i;
    if(argc!=3)
    {
        fprintf(stderr,"%s\n","drama_Shell:Enter it as kjob <process index> <signal number>\n");
        return -1;
    }

    int pid = atoi(args[1]), sig = atoi(args[2]);
    
    i=0;
    while(i < processPointer)
    {
        if(backgroundProcess[i].pid)
            count = count + 1;
        
        if(count == pid)
        {
            check = kill(backgroundProcess[i].pid,sig);
            return check;
        }
        i = i + 1;
    }
    
    if(i==processPointer)
    {
        fprintf(stderr,"%s\n","drama_Shell:Not valid process index use jobs for index\n");
        return -1;
    }
    return 0;
}   

void drama_overkill()
{  
    int count = 0;
    int i;
    
    i=0;
    while(i < processPointer)
    {
        if(backgroundProcess[i].pid)
         {
            kill(backgroundProcess[i].pid,9);
            backgroundProcess[i].pid = 0;
         }
       i = i + 1;
    }
    printf("Killed all Jobs Sucessfully ..\n");
}    



int drama_setenv(char **args)
{
    int check = 0;
    int env = 0;
    int argc = argCount(args);
    
    if(argc!=2 && argc!=3)
    {
        fprintf(stderr,"%s\n","drama_Shell:Enter as setenv <variable> or setenv <variable> <value>");
        return -1;
    }
    else if(argc==3 && env==0)
    {
        check = setenv(args[1],args[2],1);
    }
    else
    {
        check = setenv(args[1],"",1);
    }
    
    if(check < 0 && env==0)
    {
        perror("drama_Shell::Setenv:");
        return -1;
    }
    return 0;
}

int drama_unsetenv(char **args)
{   
    int check = 0;
    int argc = argCount(args);
    if(argc!=2)
    {
        fprintf(stderr,"%s\n","drama_Shell:Enter as unsetenv <variable>");
        return -1;
    }
    check = unsetenv(args[1]);
    if(check < 0)
    {
        perror("drama_Shell::Setenv:");
        return -1;
    }
    return 0;
}