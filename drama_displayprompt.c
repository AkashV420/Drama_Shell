#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];


char* display() 
{
    char str[1024];
	char str2[1024];  
    char hostname[35];
    int zero = 0;

    int uid = getuid();
		
	struct passwd *currentUser = getpwuid(uid);
	char *username = currentUser -> pw_name;
	struct utsname sysinfo;
  	
	if (uname(&sysinfo) != zero) perror("uname");
    	

    strcpy(hostname, sysinfo.nodename); 


	sprintf(str, "\e[31m<\e[34;1m%s\e[34m@\e[34;1m%s\e[31m:\e[31m",username, hostname);

	// get CWD
	getcwd(pwd, sizeof(pwd));
    char new_str[2024];
	if (strcmp(pwd, home) == 0)  strcat(str, "~>\e[32m"); 

	else {

		if (strlen(pwd) > strlen(home))
		{
			if( strncmp(pwd, home, strlen(home)) == 0)
			{
				sprintf(str2, "~%s>\e[32m",pwd + strlen(home));
				strcat(str, str2);
			}
		}
		else
		{
			sprintf(str2, "%s>\e[32m", pwd);
			strcat(str, str2);
		}
	}
	
	printf("%s", str);
	strcpy(prompt, str);
	return prompt;
}
