		#include "library.h"
		#include "functions.h"
       
		char home[1500];  
		char prompt[1500];
		char pwd[1500]; 
		char* commands[26];
		
		void signalHandlerc(int sig_num) {
			int pid;
			signal(SIGINT, signalHandlerc);
			kill(pid,SIGINT);
			pid = -1;
			printf("Ctrl+c pressed...\n");
			fflush(stdout);
		}
		void signalHandlerz(int sig_num) {
			signal(SIGTSTP, signalHandlerz);
			printf("Ctrl+z pressed... \n");
			fflush(stdout);

		}

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
			
			signal(SIGINT, signalHandlerc);
			signal(SIGTSTP, signalHandlerz);
			
			char **args;
			
			do {
				read_input = readInput();
			    i=0;
		  		while (i < read_input)
				{
				 	char *temp = malloc(1000);
				 	strcpy(temp, commands[i]);
				 	args = splitTokens(commands[i]);
					status = pipeExec(temp, args);
					
				i++;
			}
		} while(status);
			
		return 0;
		}
