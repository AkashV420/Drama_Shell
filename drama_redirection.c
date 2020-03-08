#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];

char* checkInputRedirection(char **args)
{ 
    int i;
    int argc = argCount(args);
    i=0;
    while(i < argc)
    {
        if(!strcmp(args[i],"<"))
        {
            break;
        }
      i = i + 1;
    }
    
    if(i >= argc-1)
    {
        return NULL;
    }
   
    char *ret = malloc(500);
    strcpy(ret, args[i+1]);
    
    for( ; i < argc - 2 ; i++) 
    {
        strcpy(args[i], args[i+2]);
    }
    args[i] = NULL;
    return ret;
}

char* checkOutputRedirection(char **args)
{
    int i;  
    int argc = argCount(args);
    i=0;
    while(i<argc)
    {
        if(!strcmp(args[i],">"))
        {
            break;
        }
      i = i + 1;
    }
    
    if(i >= argc-1)
    {
        return NULL;
    }
  
    char *ret = malloc(500);
    strcpy(ret, args[i+1]);
    
    for( ; i < argc - 2 ; i++) 
    {
        strcpy(args[i], args[i+2]);
    }
    args[i] = NULL;
    return ret;
}

char* checkAppendRedirection(char **args)
{
    int i;  
    int argc = argCount(args);
    i=0;
    while(i<argc)
    {
        if(!strcmp(args[i],">>"))
        {
            break;
        }
    i = i + 1;
    }
    
    if(i >= argc-1)
    {
        return NULL;
    }
   
    char *ret = malloc(500);
    strcpy(ret, args[i+1]);
    
    for( ; i < argc - 2 ; i++) 
    {
        strcpy(args[i], args[i+2]);
    }
    args[i] = NULL;
    return ret;
}


