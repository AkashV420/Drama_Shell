#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];


int backg_count;

void exited(int sig){

	pid_t wpid; //pid_t : It is a datatype which is capable of representing a process id.
	int status, zero = 0;
	wpid=wait(NULL);

	if(wpid > zero && WIFEXITED(status)==zero){ //WIFEXITED return true if child terminated normally
		printf("\nProcess with pid %d exited normally\n", wpid);
		backg_count-=1;
	}
	if(wpid > zero && WIFSIGNALED(status)==zero){ //WIFSIGNALED return true id child terminated by a signal.
		printf("\nProcess with pid %d exited due to a User-Defined signal\n", wpid);
	}
}

int drama_Proc(char **args, int flago){
	
	pid_t pid;
	int status, bg_count=0, zero = 0, temp;
	signal(SIGCHLD, exited); //	When a child process stops or terminates, SIGCHLD is sent to the parent process.
                        	// The default response to the signal is to ignore it. 
	pid = fork();

	if (pid < zero) perror("SHELL: Error Occured, can't create fork.. :(");
	
	else if (pid == zero){

		if(flago)  setpgid(0, 0);//The setpgid() function shall group processes together for the purpose of signaling, 
		                         // placement in foreground or background, and other job control actions
		
		 temp = execvp(args[0], args); // The execvp() function provide an array of pointers to null-terminated 
		                                  //strings that represent the argument list available to the new program.

		if (temp == -1) perror("SHELL: Error Executing > :(");
		exit(1);

	}
    
	/*WUNTRACED : The status of any child processes specified by pid that are stopped, 
	and whose status has not yet been reported since they stopped, shall also be 
	reported to the requesting process.*/
	if (!flago){
			do {
				waitpid(pid, &status, WUNTRACED);/*The wait() system call suspends execution of the current process 
				                                   until one of its children terminates*/
			} while (!WIFSIGNALED(status) && !WIFEXITED(status));
		}
		else
		{ 
		   // Background process
            bg_count= bg_count + 1;
			waitpid(-1, &status, WNOHANG);
			
		}

	return 1;
}