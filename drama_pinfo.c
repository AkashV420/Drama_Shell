#include "library.h"
#include "functions.h"

char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];


void drama_Pinfo(char **args, int argc){
  char pid[10];
  int zero = 0;
  char procpath[1024];
   char statpath[1024];
    char exepath[1024];
    int FileD;
    char relpath[1024];
     char name[3000];
      char **stat;
      
  if(argc > 1){  strcpy(pid, args[1]); }  // if we know the pid
  else { sprintf(pid, "%d", getpid());  } // else pinfo self

  strcpy(procpath, "/proc/");
  strcat(procpath, pid);

strcpy(statpath, procpath);
  strcat(procpath, "/stat");
  strcat(statpath, "/exe");
  
 
  int t = readlink(statpath, exepath, sizeof(exepath));
  
  if(t == -1) strcpy(exepath, "broken link");
  
  exepath[t] = '\0';

  
  
  if (strlen(exepath) > strlen(home) && strncmp(pwd, home, strlen(home)) == zero)
  {
    strcpy(relpath, "~"); strcat(relpath, exepath + strlen(home));
  }
  else strcpy(relpath, exepath);
  
 
  FileD = open(procpath, O_RDONLY);
  
  if(FileD == -1)
  {
    perror("Error");  return;
  }
 
  read(FileD, name, 250);

  stat = splitTokens(name);
  printf("pinfo\n");
  printf("pid -- %s\nProcess Status -- %s\nVirtual Memory-- %s\nExecutable Path -- %s\n", stat[0], stat[2], stat[23], exepath);
}
