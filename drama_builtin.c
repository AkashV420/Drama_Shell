#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];


int drama_Cd(int argc, char **args)
{
	//cd ~ theek kro  ===>>> THEEK KAR DIA ;) 
        
	 if (!args[1] || (strcmp("~", args[1]) == 0)) chdir(home);
	else 
	{
		if (strncmp("~", args[1], 1) == 0)
		{
			char* path = home;
			strcat(path, &args[1][1]);
			args[1] = path;
		}
		if (chdir(args[1]) == -1)
			printf("Error: Could not change directory\n");
	}
	return 1;
}

int drama_Echo (int argc, char** args) {
	int x=0;
	int val=argc;
	int i=1;
	while(i < val){
		printf("%s", args[i]);
		i++;
	}
	printf("\n");
	return x;
}

int drama_Pwd (int argc, char** args) 
{
	printf("%s",pwd);
	printf("\n");
    return 0;
}


int drama_Execute(int argc, char **args, int flago) 
{
    int zero = 0;

	if (strcmp(args[0], "pwd")==zero) {
    	drama_Pwd(argc, args);
    } 
    else if (strcmp(args[0], "cd")==zero) {
    	drama_Cd(argc ,args);
	}
	else if(strcmp(args[0],"exit")==zero || strcmp(args[0],"quit")==zero) 
	{
		printf("Exiting shell... See u next time ;)\n");
		return EXIT_SUCCESS;
    } 
	else if (strcmp(args[0], "pinfo")==zero) {
	    drama_Pinfo(args, argc); 
	}
  	else if(strcmp(args[0], "echo")==zero) {
    	drama_Echo(argc, args);
  	}
   	else if(strcmp(args[0], "ls")==zero || strcmp(args[0], "l")==zero) {
    	drama_Ls(argc, args);
	}
	else if(strcmp(args[0], "history") == 0)
	{
		printf("Abhi Nahi kiya :(\n");
	}
	else {
    return drama_Proc(args, flago);
  }
  return 1;
}
