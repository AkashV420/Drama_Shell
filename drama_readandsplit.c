#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];


int readInput()
{
	char *input = display();
    const char delimeter[2] = ";";
	int count = 0, ans;
  	ssize_t size = 0;
  	getline(&input, &size, stdin);

	if (input == NULL || strcmp(input,"\n")==0)   return 0; // when just only useless "enter" is pressed.

	commands[0] = strtok(input, delimeter); // Breaking line into commands

	while(commands[count]) 
	{ 
		commands[++count] = strtok(NULL, delimeter); 
	} // storing number of commands 
    ans=count;   //number of commands is the answer 
	return ans; 
}

char** splitTokens(char* command)
{
    int temp=0, flag=0;
    int tok=0, flag2=1;
	ssize_t bufsize = 50;
	char **tokens = malloc(bufsize * sizeof(char*)), **temp_tokens;
	
    if(!tokens)
	{
		fprintf(stderr, "Memory Allocation Error...:(");
		exit(3);
	}
	
	tokens[temp] = strtok(command, " \t\r\n\a");   // "\r" : returns the cursor to the start of the line. 

	while(tokens[temp] != NULL)
	{    

		tokens[++temp] = strtok(NULL, " \t\r\n\a");
        tok = 0;
		
		if (bufsize <= temp)
		{  
			bufsize = bufsize + 50; 
			tok = flag = 1;  
			temp_tokens = tokens; 
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens && flag2) 
			{
				free(temp_tokens);
				fprintf(stderr, "Memory Allocation Error...:(");
				exit(3);
			}
		}
	}
	
	tokens[temp] = NULL;
	return tokens; 
}
