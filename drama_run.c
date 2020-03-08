#include "library.h"
#include "functions.h"

char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];

int main(int argc, char const *argv[])
{


	int read_input;
	int status=1;
	int i;
	int pid = getpid();
	char path[1000];
	sprintf(path, "/proc/%d/exe", pid);
	readlink(path, home, 1500);

	for(int i=strlen(home);i>=0;i--)
	{
		if(home[i]=='/'){
			home[i]='\0';
			break;
		}
		home[i] = '\0';
	}
	// getcwd(home, sizeof(home));
	
	char **args;
	do {
		read_input = readInput();
	    i=0;
		while (i < read_input)
		{
			args = splitTokens(commands[i]);
			status = drama_Check(args);
			i++;
		}
	} while(status);
	return 0;
}
